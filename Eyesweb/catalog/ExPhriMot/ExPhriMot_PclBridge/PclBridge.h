#ifndef __PCL_BRIDGE_H__
#define __PCL_BRIDGE_H__

#if defined(EXPHRIMOT_PCLBRIDGE_EXPORTS) 
#   define PCLBRIDGEAPI   __declspec(dllexport)
#else 
#   define PCLBRIDGEAPI   __declspec(dllimport)
#endif  // EXPHRIMOT_PCLBRIDGE_EXPORTS

#include <string>

#endif