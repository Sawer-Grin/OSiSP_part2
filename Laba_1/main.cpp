#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define BMP_FILE "for-test.bmp"

const char g_szClassName[] = "myWindowClass";

struct _pos{
    int x;
    int y;
};  


struct _pos pos;
int speed = 10;

int isAuto = 0;
float xSpeed = 10;
float ySpeed = 0;
float realX = 0;
float realY = 0;

HBITMAP hBitmap = NULL;


float getSpeedByScreen(HWND hwnd){
    RECT rc;
    GetClientRect(hwnd, &rc);

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

    return pow(log(sqrt(width * height))/ log(700),20);
}

void processPos(RECT rc, int bmHeight, int bmWidth){

    int width = rc.right - rc.left - bmWidth;
    int height = rc.bottom - rc.top - bmHeight;

    if (pos.x > width){
        pos.x = width;
    }
    if (pos.y > height){
        pos.y = height;
    }
    if (pos.y < 0){
        pos.y = 1;
    }
    if (pos.x < 0){
        pos.x = 1;
    }

    if (isAuto == 0){
        realX = pos.x;
        realY = pos.y;
    }
}

void changePosOrSpeedInAuto(RECT rc, int bmHeight, int bmWidth){

    int width = rc.right - rc.left - bmWidth;
    int height = rc.bottom - rc.top - bmHeight;

    realX += xSpeed;
    realY += ySpeed;

    pos.x = (int) realX;
    pos.y = (int) realY;

    if (pos.x < 0 || pos.x > width){
        xSpeed = -xSpeed;
    }
    if (pos.y < 0 || pos.y > height){
        ySpeed = -ySpeed;
    }
}

void DrawSprite(HWND hwnd, LPPAINTSTRUCT lpPS){
    RECT rcUser;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;

    GetClientRect(hwnd, &rcUser);

    hdcMem = CreateCompatibleDC(lpPS->hdc);
    hbmMem = CreateCompatibleBitmap(lpPS->hdc,
                                    rcUser.right-rcUser.left,
                                    rcUser.bottom-rcUser.top);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(hdcMem, &rcUser, hbrBkGnd);
    DeleteObject(hbrBkGnd);

    BITMAP bm;
    GetObject(hBitmap, sizeof(bm), &bm);

    if (isAuto){
        changePosOrSpeedInAuto(rcUser, bm.bmHeight, bm.bmWidth);
    }

    processPos(rcUser, bm.bmHeight, bm.bmWidth);

    HDC hdcSprite = CreateCompatibleDC(hdcMem);
    HBITMAP oldSprite = (HBITMAP)SelectObject(hdcSprite, hBitmap);
    BitBlt(hdcMem, pos.x,pos.y, pos.x + bm.bmWidth, pos.y + bm.bmHeight, hdcSprite, 0,0, SRCCOPY);
    DeleteDC(hdcSprite);

    BitBlt(lpPS->hdc,
           rcUser.left, rcUser.top,
           rcUser.right-rcUser.left, rcUser.bottom-rcUser.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    switch(msg)
    {
        case WM_CREATE:
            pos.x = 0;
            pos.y = 0;
            hBitmap = (HBITMAP)LoadImage(NULL, BMP_FILE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        break;
        case WM_ERASEBKGND:
            return (LRESULT)1;
        case WM_PAINT: {
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawSprite(hwnd, &ps);
            EndPaint(hwnd, &ps);
            if (isAuto)
                InvalidateRect(hwnd, NULL, 0);
            break;
        }
        case WM_KEYDOWN:
            if (wParam == VK_LEFT){
                pos.x -= speed;
            }
            else if (wParam == VK_RIGHT){
                pos.x += speed;
            }
            else if (wParam == VK_UP){
                pos.y -= speed;
            }
            else if (wParam == VK_DOWN){
                pos.y += speed;
            }
            isAuto = 0;
            InvalidateRect(hwnd, NULL, 0);
        break;
        case WM_MOUSEWHEEL:
            if (GET_KEYSTATE_WPARAM(wParam) == MK_SHIFT)
                pos.x -= (int) GET_WHEEL_DELTA_WPARAM(wParam) / 20;
            else
                pos.y -= (int) GET_WHEEL_DELTA_WPARAM(wParam) / 20;
            isAuto = 0;
            InvalidateRect(hwnd, NULL, 0);
        break;
        case WM_KEYUP:
        if (wParam == VK_TAB){
            isAuto = 1;
            float mult = getSpeedByScreen(hwnd);
            if (mult > 1){
                xSpeed = rand() % (int) mult - mult/2;
                ySpeed = rand() % (int) mult - mult/2;
            }
            else{
                int isMinusX = rand() % 2 == 0 ? -1 : 1;
                int isMinusY = rand() % 2 == 0 ? -1 : 1;
                xSpeed = ((double)rand() / (double)RAND_MAX) * mult * isMinusX;
                ySpeed = ((double)rand() / (double)RAND_MAX) * mult * isMinusY;
            }
            InvalidateRect(hwnd, NULL, 0);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, 0);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;


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
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    srand(time(NULL));

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}