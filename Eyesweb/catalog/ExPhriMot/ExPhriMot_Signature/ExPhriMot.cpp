// ExPhriMot.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

using namespace Eyw;

static CSTR g_szDllIdentifier = "EXPHRIMOT_{3915502C-AC86-4586-A23F-B630B919AD72}";


BOOL APIENTRY DllMain( HMODULE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		if( !SDKInit( hModule, g_szDllIdentifier ) )
			return FALSE;
		break;

	case DLL_PROCESS_DETACH:
		SDKDone();
		break;
	}

    return TRUE;
}

