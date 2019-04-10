#include "../include/WebServer.h"
#include "../include/Handler.h"

#include <glog/logging.h>


void wyx::WebServer::init(){
	this->resource.reset(wyx::Handler::getWebResource());
}


void wyx::WebServer::start(){
	// 对请求路径和方法进行匹配查找，并生成响应
	decltype(this->resource->begin()) res_iter; 
	for(res_iter = this->resource->begin(); res_iter != resource->end(); res_iter++){

		std::regex regex_method(res_iter->first);
		std::smatch sm_result;
		string path_info = getenv("PATH_INFO");
		string request_method = getenv("REQUEST_METHOD");

		//匹配路径
		if(std::regex_match(path_info,sm_result,regex_method)==true){
			LOG(INFO)<<"find res_iter[]="<<res_iter->first;
			LOG(INFO)<<"path_info="<<path_info;

			//判断method是否定义(GET/POST等)
			if(res_iter->second.count(request_method)>0){
				//调用相应的方法GET/POST等
				LOG(INFO)<<"find request_method="<<request_method;
				res_iter->second[request_method]();
			}else {
				LOG(ERROR)<<"request_method not found:"<<request_method;
			}
			break;
		}
	}

	if(res_iter == resource->end()){
		LOG(ERROR)<<"path not found:"<<getenv("PATH_INFO");
	}
}


