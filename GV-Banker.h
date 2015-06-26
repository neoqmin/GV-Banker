/**
	@file		GV-Banker.h
	@brief		It's function set to share enviorment variables.
	@note		[Function]\n
				1. create enviorment variables in main process using CreateFileMapping api.\n
				2. use enviorment in kernel mode using ZwOpenSection and MmMapViewInSystemSpace.\n
				3. use enviorment in user mode using OpenFileMapping and MpaViewOfFile.
*/
#ifndef _GV_BANKER_H_
#define _GV_BANKER_H_

/**
	@struct		USER_DEFINE_STRUCT
	@brief		struct sample for GV_RESOURCE
	@date		2015.06.26
	@author		황규민
*/
typedef struct _USER_DEFINED_STRUCT {
	ULONG		Data1;
	ULONG		Data2;
} USER_DEFINED_STRUCT, *PUSER_DEFINED_STRUCT;

#define GV_RESOURCE_NAME		L"HereisResourceName"		///< Resource name of global variables
#define GV_RESOURCE_SIZE		sizeof(USER_DEFINE_STRUCT)	///< Length of resource

/**
	@brief		This functionis is getting resource.
	@param[in]	pResource		Resource pointer
	@return		ERROR_SUCCESS	Success
	@return		ULONG			Error code(GetLastCode() or NTSTATUS)
	@date		2015.06.26
	@author		Kevin Hwang
*/
ULONG
VrGetResource(IN PVOID pResource, IN ULONG ulLength);

/**
	@brief		This functionis is setting resource.
	@param[out]	pResource		Resource pointer
	@return		ERROR_SUCCESS	Success
	@return		ULONG			Error code(GetLastCode() or NTSTATUS)
	@date		2015.06.26
	@author		Kevin Hwang
*/
ULONG
VrSetResource(OUT PVOID pResource, IN ULONG ulLength);

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
VrCreateResource(PVOID pResurce, ULONG ulLength);

/**
	@brief		delete resource.
	@date		2015.06.26
	@author		황규민
*/
VOID
VrDeleteResource();

#endif
