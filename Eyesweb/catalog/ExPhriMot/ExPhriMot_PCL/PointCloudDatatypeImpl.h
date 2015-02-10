#ifndef __POINTCLOUD_DATATYPE_IMPL_H__
#define __POINTCLOUD_DATATYPE_IMPL_H__

#include "PointCloudDatatype.h"

class CPointCloudDatatypeInitInfoImpl: public Eyw::CDatatypeInitInfoImpl<IPointCloudDatatypeInitInfo>
{
public:
	CPointCloudDatatypeInitInfoImpl( const Eyw::OBJECT_CREATIONCTX* pCtx );

// ITrackerStateInitInfo
public:
    virtual EYWAPI ~CPointCloudDatatypeInitInfoImpl();

};

////////////////////////////////////////////////////////////////////////////////////
class CPointCloudDatatypeImpl : public Eyw::CDatatypeImpl<IPointCloudDatatype>
{
public:
	CPointCloudDatatypeImpl( const Eyw::OBJECT_CREATIONCTX* pCtx );
	
// ISerialize
	virtual Eyw::PMEM_BUF EYWAPI Serialize() const;
	virtual void EYWAPI ReleaseBuffer( Eyw::PMEM_BUF pBuf ) const;
	virtual bool EYWAPI Unserialize( Eyw::PCMEM_BUF pBuf );

	virtual Eyw::STR EYWAPI SerializeAsText() const;
	virtual void EYWAPI ReleaseText( Eyw::STR str ) const;

// IPointCloudDatatype

public:
	virtual EYWAPI ~CPointCloudDatatypeImpl();

private:
	// Here place the data members of the datatype
};

#endif