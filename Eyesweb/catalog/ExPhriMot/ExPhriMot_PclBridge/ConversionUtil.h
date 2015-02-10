#ifndef __PCL_UTIL_H__
#define __PCL_UTIL_H__

#if defined(EXPHRIMOT_PCLBRIDGE_EXPORTS) 
#   define PCLBRIDGEAPI   __declspec(dllexport)
#else 
#   define PCLBRIDGEAPI   __declspec(dllimport)
#endif  // EXPHRIMOT_PCLBRIDGE_EXPORTS

#include <string>

namespace ExPhriMot{
	namespace PclBridge{
		class PCLBRIDGEAPI ConversionUtil
		{
		public:
			ConversionUtil();
			~ConversionUtil();
			static bool PlyToPcd(const std::string& inputFile, const std::string& outputFile, bool binaryFormat);
			static bool MeshToPcd(const std::string& inputFile, const std::string& outputFile);

		};
	}
}

#endif // ifndef