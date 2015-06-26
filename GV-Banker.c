/**
	@file		GV-Banker.cpp
	@brief		It's function set to share enviorment variables.
*/
#include <windows.h>
#include "GV-Banker.h"

#define GV_RESOURCE_NAME_USER		L"Global\\"##GV_RESOURCE_NAME				///< resource name for user mode.

/**
	@brief		It's main handle of map file.\n
				It is created by application.\n
				It's only one.\n
				Map file is deleted if to close handle.
*/
HANDLE		g_hMapFile = NULL;

/**
	@brief		This functionis is getting resource.
	@param[in]	pResource		Resource pointer
	@return		ERROR_SUCCESS	Success
	@return		ULONG			Error code(GetLastCode() or NTSTATUS)
	@date		2015.06.26
	@author		Kevin Hwang
*/
ULONG
VrGetResource(IN PVOID pResource, IN ULONG ulLength)
{
	DWORD		dwRet = ERROR_SUCCESS;

	HANDLE		hFileMap = OpenFileMapping(FILE_MAP_READ, FALSE, GV_RESOURCE_NAME_USER);
	if(hFileMap) {
		PVOID	pTemp;
		pTemp = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, ulLength);
		if(pTemp) {
			RtlCopyMemory(pResource, pTemp, ulLength);

			UnmapViewOfFile(pTemp);
		} else {
			dwRet = GetLastError();
		}

		CloseHandle(hFileMap);
	} else {
		dwRet = GetLastError();
	}

	return dwRet;
}

/**
	@brief		This functionis is setting resource.
	@param[out]	pResource		Resource pointer
	@return		ERROR_SUCCESS	Success
	@return		ULONG			Error code(GetLastCode() or NTSTATUS)
	@date		2015.06.26
	@author		Kevin Hwang
*/
ULONG
VrSetResource(OUT PVOID pResource, IN ULONG ulLength)
{
	DWORD		dwRet = ERROR_SUCCESS;

	HANDLE		hFileMap = OpenFileMapping(FILE_MAP_READ, FALSE, GV_RESOURCE_NAME_USER);
	if(hFileMap) {
		PVOID	pTemp;
		pTemp = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, ulLength);
		if(pTemp) {
			RtlCopyMemory(pTemp, pResource, ulLength);

			UnmapViewOfFile(pTemp);
		} else {
			dwRet = GetLastError();
		}

		CloseHandle(hFileMap);
	} else {
		dwRet = GetLastError();
	}

	return dwRet;
}

/**
	@brief		Initialize resource,
	@param[in]	pResource		Resource pointer
	@param[in]	ulLength		Size of resource
	@return		ERROR_SUCCESS	Success(or STATUS_SUCCESS)
	@return		ULONG			Error code(GetLastCode() or NTSTATUS)
	@date		2015.06.26
	@author		Kevin Hwang
*/
ULONG
VrCreateResource(PVOID pResurce, ULONG ulLength)
{
	ULONG		ulRet = 0;

	g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, ulLength, GV_RESOURCE_NAME_USER); 
	if(g_hMapFile == NULL) {
		ulRet = GetLastError();
	}

	return ulRet;
}

/**
	@brief		delete resource.
	@date		2015.06.26
	@author		Kevin Hwang
*/
VOID
VrDeleteResource() {
	if(g_hMapFile) {
		CloseHandle(g_hMapFile);
	}
}
