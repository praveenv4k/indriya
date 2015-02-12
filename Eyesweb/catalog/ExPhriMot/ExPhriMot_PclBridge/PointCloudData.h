#ifndef __POINTCLOUD_DATA_H__
#define __POINTCLOUD_DATA_H__

#include "PclBridge.h"
#include "Eigen\Eigen"

namespace ExPhriMot{
	namespace PclBridge{
		enum PCLBRIDGEAPI PointCloudFieldType{

		};

		struct PCLBRIDGEAPI PointCloudField{
			std::string Name;
			PointCloudFieldType Type;
			int Count;
		};

		class PCLBRIDGEAPI PointCloudData{
		public:
			 long GetWidth() const;
			 long GetHeight() const;
			 long GetSize() const;
			 void GetFieldsInfo(std::vector<PointCloudField>& fieldInfo) const;
			 void GetSensorOrientation(Eigen::Quaternionf& orient);
			 void GetSensorPosition(Eigen::Vector3f& pos);
			 void GetData(byte** ppData);
		};
	}
}

#endif