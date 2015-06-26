/**
	@file		GV-Banker.cpp
	@brief		It's function set to share enviorment variables.
*/
#include <ntddk.h>
#include "GV-Banker.h"

#define GV_RESOURCE_NAME_KRNL		L"\\BaseNamedObjects\\"##GV_RESOURCE_NAME	///< resource name for kernel mode.

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
	NTSTATUS			ntStatus = STATUS_SUCCESS;
	UNICODE_STRING		ustrResourceName;
	OBJECT_ATTRIBUTES	objAttr;
	HANDLE				hSection = NULL;

	RtlInitUnicodeString(&ustrResourceName, GV_RESOURCE_NAME_KRNL);
	InitializeObjectAttributes(&objAttr, &ustrResourceName, OBJ_CASE_INSENSITIVE, NULL, NULL);
	ntStatus = ZwOpenSection(&hSection, SECTION_ALL_ACCESS, &objAttr);
	if(NT_SUCCESS(ntStatus)) {
		PVOID		SectionObject	= NULL;

		ntStatus = ObReferenceObjectByHandle(hSection, SECTION_MAP_READ|SECTION_MAP_WRITE, NULL, KernelMode, &SectionObject, NULL);
		if(NT_SUCCESS(ntStatus)) {
			SIZE_T		nLength = ulLength;
			PVOID		pTemp = NULL;

			ntStatus = MmMapViewInSystemSpace(SectionObject, &pTemp, &nLength);
			if(NT_SUCCESS(ntStatus)) {
				RtlCopyMemory(pResource, pTemp, ulLength);
				
				MmUnmapViewInSystemSpace(pTemp);
			}
			ObDereferenceObject(SectionObject);
		}

		ZwClose(hSection);
	}

	return ntStatus;
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
	NTSTATUS			ntStatus = STATUS_SUCCESS;
	UNICODE_STRING		ustrResourceName;
	OBJECT_ATTRIBUTES	objAttr;
	HANDLE				hSection = NULL;

	RtlInitUnicodeString(&ustrResourceName, GV_RESOURCE_NAME_KRNL);
	InitializeObjectAttributes(&objAttr, &ustrResourceName, OBJ_CASE_INSENSITIVE, NULL, NULL);
	ntStatus = ZwOpenSection(&hSection, SECTION_ALL_ACCESS, &objAttr);
	if(NT_SUCCESS(ntStatus)) {
		PVOID		SectionObject	= NULL;

		ntStatus = ObReferenceObjectByHandle(hSection, SECTION_MAP_READ|SECTION_MAP_WRITE, NULL, KernelMode, &SectionObject, NULL);
		if(NT_SUCCESS(ntStatus)) {
			SIZE_T		nLength = ulLength;
			PVOID		pTemp = NULL;

			ntStatus = MmMapViewInSystemSpace(SectionObject, &pTemp, &nLength);
			if(NT_SUCCESS(ntStatus)) {
				RtlCopyMemory(pTemp, pResource, ulLength);
				
				MmUnmapViewInSystemSpace(pTemp);
			}
			ObDereferenceObject(SectionObject);
		}

		ZwClose(hSection);
	}

	return ntStatus;
}
