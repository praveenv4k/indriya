#ifndef __POINTCLOUD_DATATYPE_H__
#define __POINTCLOUD_DATATYPE_H__

#include "..\ExPhriMot_Signature\Signature.h"
#define EYW_POINT_CLOUD_DATATYPE "PointCloudDatatype"

class IPointCloudDatatypeInitInfo : public Eyw::IDatatypeInitInfo
{
	EYW_DECLARE_INTERFACE( IPointCloudDatatypeInitInfo );

public:
};

enum PointCloudFieldType{

};

struct PointCloudField{
	std::string Name;
	PointCloudFieldType Type;
	int Count;
};

class IPointCloudDatatype : public Eyw::IDatatype
{
	EYW_DECLARE_INTERFACE( IPointCloudDatatype );

public:
	// Add here the API of the new datatype
	virtual long EYWAPI GetWidth() const = 0;
	virtual long EYWAPI GetHeight() const = 0;
	virtual void EYWAPI GetFieldInfo(std::vector<PointCloudField>& fieldInfo) const = 0;

};

EYW_DATATYPE_TRAITS( IPointCloudDatatype, EYW_EXPHRIMOT_CATALOG_ID , EYW_POINT_CLOUD_DATATYPE );
EYW_SMART_POINTERS( IPointCloudDatatype, point_cloud_datatype );

#endif
