// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX

#include <windows.h>

#include <EywSDK.h>

// The SystemCatalog SDK is needed if you plan to develop blocks using image or audio datatatypes. 
// Since this is very common in EyesWeb, it is included by default.
#include <EywSystemCatalogSDK.h>