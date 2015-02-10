#include "StdAfx.h"
#include "PointCloudDatatypeImpl.h"
#include "..\ExPhriMot_Signature\Signature.h"
#include <strstream>

////////////////////////////////////////////////////////////////////////////////////
// Signature
Eyw::datatype_class_registrant g_PointCloudDatatype( 
	Eyw::datatype_class_registrant::datatype_id( "PointCloudDatatype" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "PointCloudDatatype" )
			.description( "Point cloud library PCD" )
		.end_language()	
		.begin_authors()
			.author( EYW_EXPHRIMOT_CATALOG_AUTHOR_ID )
		.end_authors()
		.begin_licences()
			.licence( EYW_EXPHRIMOT_LICENSE_ID  )
		.end_licences()
		.begin_companies()
			.company( EYW_EXPHRIMOT_COMPANY_ID )
		.end_companies()
		.default_factory<CPointCloudDatatypeImpl>()
		.default_init_info_factory<CPointCloudDatatypeInitInfoImpl>()
	);

////////////////////////////////////////////////////////////////////////////////////
CPointCloudDatatypeInitInfoImpl::CPointCloudDatatypeInitInfoImpl( const Eyw::OBJECT_CREATIONCTX* pCtx )
:	Eyw::CDatatypeInitInfoImpl<IPointCloudDatatypeInitInfo>( pCtx )
{
}

CPointCloudDatatypeInitInfoImpl::~CPointCloudDatatypeInitInfoImpl()
{
}

////////////////////////////////////////////////////////////////////////////////////
CPointCloudDatatypeImpl::CPointCloudDatatypeImpl( const Eyw::OBJECT_CREATIONCTX* pCtx )
:	Eyw::CDatatypeImpl<IPointCloudDatatype>( pCtx )
{
}

EYWAPI CPointCloudDatatypeImpl::~CPointCloudDatatypeImpl()
{
}

Eyw::PMEM_BUF EYWAPI CPointCloudDatatypeImpl::Serialize() const
{
	Eyw::PMEM_BUF pRet = NULL;
	// TODO: allocate a structure and fill it with the content of the relevant data members
	/* e.g.
	pRet = Eyw::CreateMemBuffer( sizof(XYZ) );
	if( pRet != 0 )
	{
		XYZ* pTarget=(XYZ*)pRet->_pBuf;
		pTarget->_x=_X;
		...
	}
	*/
	return pRet;
}

void EYWAPI CPointCloudDatatypeImpl::ReleaseBuffer( Eyw::PMEM_BUF pBuf ) const
{
	DestroyMemBuffer( pBuf );
}

bool EYWAPI CPointCloudDatatypeImpl::Unserialize( Eyw::PCMEM_BUF pBuf )
{
	if( pBuf == 0 )
		return true;

	// TODO: cast pBuf->_pBuf to the appropriate structure and read the data from there

	return true;
}

Eyw::STR EYWAPI CPointCloudDatatypeImpl::SerializeAsText() const
{
	std::strstream s;
	// TODO: Serialize the data members
	/* e.g.
	s << "Label = " << _value << '\0';
	*/
	return _strdup( s.str() );
}

void EYWAPI CPointCloudDatatypeImpl::ReleaseText( Eyw::STR str ) const
{
	if( str )
		free( str );
}

////////////////////////////////////////////////////////////////////////////////////
