#ifndef __PARAM_HELPER_H__
#define __PARAM_HELPER_H__

#include "Indriya\Msgs\node.pb.h"
#include <boost\any.hpp>
#include <boost\lexical_cast.hpp>

class ParameterHelper{
public:
	static bool GetParamString(const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Param >& params,
		const std::string& key, std::string& paramValue){
		bool ret = false;
		int size = params.size();
		for (int i = 0; i < size; i++){
			const Indriya::Core::Msgs::Param& param = params.Get(i);
			if (param.key() == key){
				paramValue = param.value();
				ret = true;
				break;
			}
		}
		return ret;
	}

	template <typename T>
	static T GetParam(const ::google::protobuf::RepeatedPtrField< ::Indriya::Core::Msgs::Param >& params,
		const std::string& key, T defaultValue){
		T ret = defaultValue;
		std::string paramValue;
		if (GetParamString(params, key, paramValue)){
			ret = boost::lexical_cast<T>(paramValue);
		}
		return ret;
	}
};

#endif