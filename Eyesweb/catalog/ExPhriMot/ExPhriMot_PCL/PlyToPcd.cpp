#include "StdAfx.h"
#include "PlyToPcd.h"
#include "resource.h"
#include "../ExPhriMot_Signature/Signature.h"
using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant g_PlyToPcd( 
	Eyw::block_class_registrant::block_id( "PlyToPcd" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "PlyToPcd" )
			.description( "This block converts PLY File to PCD file"	)
			.libraries( "ExPhriMot.PCL.Converters" )
			.bitmap( IDB_PLYTOPCD_BITMAP )
		.end_language()	
		.begin_authors()
			.author( EYW_EXPHRIMOT_CATALOG_AUTHOR_ID )
		.end_authors()
		.begin_companies()
		.company(EYW_EXPHRIMOT_COMPANY_ID)
		.end_companies()
		.begin_licences()
			.licence(EYW_EXPHRIMOT_LICENSE_ID )
		.end_licences()
		.default_factory< CPlyToPcd >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define PARAMETER_OUTPUTPCDFILE "Output PCD File"
#define INPUT_INPUTPLYFILE "Input PLY File"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CPlyToPcd::CPlyToPcd( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	_pInInputPLYFile=NULL;

	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged( INPUT_INPUTPLYFILE, true );

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CPlyToPcd::~CPlyToPcd()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CPlyToPcd::InitSignature()
{	 
	_pParamOutputPCDFile= Eyw::Cast<Eyw::IString*>(
	                     SetParameter(Eyw::pin::id(PARAMETER_OUTPUTPCDFILE)
	                         .name("Output PCD File")
	                         .description("File Name")
	                         .type<Eyw::IString>()
	                         )->GetDatatype() );
	SetInput(Eyw::pin::id(INPUT_INPUTPLYFILE)
	    .name("Input PLY File")
	    .description("File name")
	    .type<Eyw::IString>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CPlyToPcd::CheckSignature()
{
	_pParamOutputPCDFile=get_parameter_datatype<Eyw::IString>(PARAMETER_OUTPUTPCDFILE);
	_signaturePtr->GetInputs()->FindItem( INPUT_INPUTPLYFILE );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CPlyToPcd::DoneSignature()
{
	_pParamOutputPCDFile=NULL;

}

/// Block Actions

//////////////////////////////////////////////////////////
/// <summary>
/// Block initialization action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CPlyToPcd::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		_pInInputPLYFile = get_input_datatype<Eyw::IString>( INPUT_INPUTPLYFILE );

    	return true;
    }
    catch(...)
    {
        return false;
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block start action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CPlyToPcd::Start() throw()
{
    try
    {
    	/// TODO: add your logic
    	return true;
    }
    catch(...)
    {
        return false;
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block execution action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CPlyToPcd::Execute() throw()
{
    try
    {
    	/// TODO: add your logic
    }
    catch(...)
    {
    }
	return true;
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block stop action.
/// </summary>
//////////////////////////////////////////////////////////
void CPlyToPcd::Stop() throw()
{
    try
    {
    }
    catch(...)
    {
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block deinitialization action.
/// </summary>
//////////////////////////////////////////////////////////
void CPlyToPcd::Done() throw()
{
    try
    {
		_pInInputPLYFile = NULL;

    }
    catch(...)
    {
    }
}

/// optionals

//////////////////////////////////////////////////////////
/// <summary>
/// Manage the ChangedParameter event.
/// </summary>
/// <param name="csParameterID">
/// [in] id of the changed parameter.
/// </param>
//////////////////////////////////////////////////////////
void CPlyToPcd::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}
