#pragma once


#include <ntddk.h>
#include <windef.h>
#include <stdlib.h>
#include <ntimage.h>
#include "second_task.h"
#include "logger.h"

#define dprintf				if (DBG) DbgPrint

#define	DEVICE_NAME			L"\\Device\\CmRegMonitor"
#define LINK_NAME			L"\\DosDevices\\CmRegMonitor"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\CmRegMonitor"

VOID DriverUnload(PDRIVER_OBJECT pDriverObj);
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString);

