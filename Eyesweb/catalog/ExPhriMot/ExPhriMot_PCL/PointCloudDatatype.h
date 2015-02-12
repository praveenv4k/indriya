#ifndef __POINTCLOUD_DATATYPE_H__
#define __POINTCLOUD_DATATYPE_H__

#include "..\ExPhriMot_Signature\Signature.h"
#include "..\ExPhriMot_PclBridge\PointCloudData.h"

#define EYW_POINT_CLOUD_DATATYPE "PointCloudDatatype"

class IPointCloudDatatypeInitInfo : public Eyw::IDatatypeInitInfo
{
	EYW_DECLARE_INTERFACE( IPointCloudDatatypeInitInfo );

public:
};



class IPointCloudDatatype : public Eyw::IDatatype
{
	EYW_DECLARE_INTERFACE( IPointCloudDatatype );

public:
	// Add here the API of the new datatype
	/*virtual long EYWAPI GetWidth() const = 0;
	virtual long EYWAPI GetHeight() const = 0;
	virtual long EYWAPI GetSize() const = 0;
	virtual void EYWAPI GetFieldsInfo(std::vector<PointCloudField>& fieldInfo) const = 0;
	virtual void EYWAPI GetSensorOrientation(Eigen::Quaternionf& orient) = 0;
	virtual void EYWAPI GetSensorPosition(Eigen::Vector3f& pos) = 0;
	virtual void EYWAPI GetData(byte** ppData) = 0; */
	virtual void EYWAPI GetPointCloud(boost::shared_ptr<ExPhriMot::PclBridge::PointCloudData>& cloud) = 0;
};

EYW_DATATYPE_TRAITS( IPointCloudDatatype, EYW_EXPHRIMOT_CATALOG_ID , EYW_POINT_CLOUD_DATATYPE );
EYW_SMART_POINTERS( IPointCloudDatatype, point_cloud_datatype );

#endif
