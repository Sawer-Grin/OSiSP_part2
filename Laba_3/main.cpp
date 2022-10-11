#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <commctrl.h>
#include <tchar.h>

#define amount_in_line 4
#define amount_in_column 5
#define default_height_line_text 20

const char g_szClassName[] = "myWindowClass";
int size_width = 500;
int size_height = 500;

int position_scroll = 0;
SCROLLINFO scroll;

HWND table[amount_in_column][amount_in_line];

void initialTable(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    int item_width = width / amount_in_line;
    int item_height = default_height_line_text * 3;

    for (int i = 0; i < amount_in_column; i++) {
        for (int j = 0; j < amount_in_line; j++) {
            int x  = j * item_width;
            int y = i * item_height;

            table[i][j] = CreateWindow("EDIT",
                0, 
                WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE,
                x, y, item_width, item_height,
                hwnd,
                (HMENU)20,
                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
        }
    }
}

void destroyTable(HWND hwnd) {
    for (int i = 0; i < amount_in_column; i++) {
        for (int j = 0; j < amount_in_line; j++) {
            DestroyWindow(table[i][j]);
        }
    }
}

int find_max_str_item(HWND table_line[]){

    int max_line = SendMessage(table_line[0], EM_GETLINECOUNT, NULL, NULL);
    for (int i = 0; i < amount_in_line; i++) {
        int temp = SendMessage(table_line[i], EM_GETLINECOUNT, NULL, NULL);
        if (temp > max_line)
            max_line = temp;
    }
    return max_line;
}

void updateTable(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    int item_width = width / amount_in_line;
    int y_now = 0;

    for (int i = 0; i < amount_in_column; i++) {
        int max_lines = find_max_str_item(table[i]);
        int item_height = default_height_line_text * (
            max_lines + 1
        );

        for (int j = 0; j < amount_in_line; j++) {
            int x = j * item_width;
            MoveWindow(table[i][j], x, y_now - position_scroll, item_width, item_height, TRUE);
        }

        y_now += item_height;
    }
}

int get_height_column(int amount_columns) {
    RECT rect;
    int height = 0;

    for (int i = 0; i < amount_columns; i++) {
        GetWindowRect(table[i][0], &rect);
        height += (rect.bottom = rect.top);
    }
    return height;
}

void processScrolling(HWND hwnd, WPARAM wparam) {
    SCROLLINFO temp_scroll;

    temp_scroll.cbSize = sizeof(SCROLLINFO);
    temp_scroll.fMask = SIF_ALL;

    GetScrollInfo(hwnd, SB_VERT, &temp_scroll);
    int pos = temp_scroll.nPos;

    switch (LOWORD(wparam)) {
        case SB_THUMBPOSITION:
            pos = HIWORD(wparam);
        break;
        case SB_LINEDOWN:
            pos++;
        break;
        case SB_LINEUP:
            pos--;
        break;
    }

    if (temp_scroll.nPos != pos) {
        position_scroll = get_height_column(pos);
        updateTable(hwnd);
        SetScrollPos(hwnd, SB_VERT, pos, TRUE);
    }

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndListView;
    static int inputReady = true;
    switch(msg)
    {
        case WM_CREATE:{
            initialTable(hwnd);
            break;
        }
        case WM_SIZE:{
            updateTable(hwnd);
            InvalidateRect(hwnd, NULL, 0);
            updateTable(hwnd);
            break;
        }
        case WM_COMMAND:{
            if (HIWORD(wParam) == EN_CHANGE)
                updateTable(hwnd);
            break;
        }
        case WM_GETMINMAXINFO:
        {
            MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
            POINT ptMin = { 200, 200 };
            pInfo->ptMinTrackSize = ptMin;
            break;
        }
        case WM_VSCROLL: {
            processScrolling(hwnd, wParam);
            break;
        }
        case WM_CLOSE:
            destroyTable(hwnd);
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    /// Initialise the main settings 

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Laba_2",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT, size_width, size_height,
        NULL, NULL, hInstance, NULL);

    SCROLLINFO scroll;
    scroll.nPos = 0;
    scroll.nMin = 0;
    scroll.nMax = amount_in_column - 1;
    scroll.nPage = 1;
    scroll.fMask = SIF_ALL;

    SetScrollInfo(hwnd, SB_VERT, &scroll, TRUE);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}