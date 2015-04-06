#include "stdafx.h"
#include "ConversionUtil.h"
#include "ConversionUtilImpl.h"

ExPhriMot::PclBridge::ConversionUtil::ConversionUtil()
{
}


ExPhriMot::PclBridge::ConversionUtil::~ConversionUtil()
{
}

bool ExPhriMot::PclBridge::ConversionUtil::PlyToPcd(const std::string& inputFile, const std::string& outputFile, bool binaryFormat){
	bool ret = false;
	try{
		pcl::PCLPointCloud2 cloud;
		if (ConversionUtilImpl::LoadCloud(inputFile, cloud)){
			// Convert to PLY and save
			ConversionUtilImpl::SaveCloud(outputFile, cloud, binaryFormat);
			ret = true;
		}
	}
	catch (...){

	}
	return ret;
}

bool ExPhriMot::PclBridge::ConversionUtil::MeshToPcd(const std::string& inputFile, const std::string& outputFile){
	bool ret = false;
	try{
		ret = true;
	}
	catch (...){
	}
	return ret;
}