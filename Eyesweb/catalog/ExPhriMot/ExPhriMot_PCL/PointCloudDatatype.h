#pragma once

#include "..\ExPhriMot_Signature\Signature.h"
#define EYW_POINT_CLOUD_DATATYPE	"PointCloudDatatype"

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
};

EYW_DATATYPE_TRAITS( IPointCloudDatatype, EYW_EXPHRIMOT_CATALOG_ID , EYW_POINT_CLOUD_DATATYPE );
EYW_SMART_POINTERS( IPointCloudDatatype, point_cloud_datatype );
