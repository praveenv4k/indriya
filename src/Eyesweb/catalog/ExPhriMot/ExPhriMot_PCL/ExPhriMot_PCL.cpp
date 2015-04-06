// ExPhriMot_PCL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../ExPhriMot_Signature/Signature.h"

using namespace Eyw;

static CSTR g_szDllIdentifier = "EXPHRIMOT_PCL_{8919C9F7-6A97-4D66-86EA-AA1693E75A1C}";


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

/**
* \var exphrimotCatalog
* We istantiate an object of type catalog_class_registrant just to tell EyesWeb that this dll is part of the exphrimot catalog.
*/
static catalog_class_registrant complexCatalog(
	catalog_class_registrant::catalog_id(EYW_EXPHRIMOT_CATALOG_ID)
	.begin_language(EYW_LANGUAGE_US_ENGLISH)
	.name("ExPhriMot Catalog")
	.end_language()
	);
