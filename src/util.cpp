#include "../include/util.h"
#include <unistd.h>

using namespace std;
using namespace wyx;


vector<string>* wyx::string_split(const string& str, const string& delims){
	string::size_type pos1,pos2;
	pos2 = str.find(delims);
	pos1 = 0;

	vector<string>* result = new vector<string>();
	while(string::npos != pos2){
		result->push_back(str.substr(pos1,pos2-pos1));

		pos1 = pos2 + delims.length();
		pos2 = str.find(delims,pos1);
	}
	if(pos1 != str.length()){
		result->push_back(str.substr(pos1));
	}

	return result;
}

ParamUtil::ParamUtil(const string &param):param(param){}

unordered_multimap<string,string>* ParamUtil::getParamMultimap(const string &delims){
	unordered_multimap<string,string> *result = new unordered_multimap<string,string>();
	shared_ptr<vector<string>> segment_list (string_split(this->param,delims));
	for(string &item : *segment_list){
		string::size_type equal_sign_pos = item.find("=");
		// 如果等号在开头，或者没有等号，那么此段参数格式错误，跳过
		if(equal_sign_pos == 0 || equal_sign_pos == string::npos){
			LOG(WARNING)<<"getParamMultimap WARNING : 等号格式错误";
			continue;
		}
		shared_ptr<vector<string>> param (string_split(item,"="));
		if(param->size()==0 || param->size()>2){
			LOG(WARNING)<<"getParamMultimap WARNING : 参数数量错误";
			continue;
		}else if(param->size() == 1){
			LOG(INFO)<<"getParamMultimap INFO : 空值";
			result->insert(pair<string,string>(param->at(0),""));
		}else{
			result->insert(pair<string,string>(param->at(0),param->at(1)));
		}
	}
	return result;
}

string* ParamUtil::getParamValue(const string &key,const string &delims){
	if(!paramMultimap){
		paramMultimap.reset(this->getParamMultimap(delims));
	}
	unordered_multimap<string,string>::const_iterator pairs = paramMultimap->find(key);

	if(pairs == paramMultimap->end()){
		LOG(INFO)<<"未找到 param value of key:"<<key;
		return nullptr;
	}else{
		LOG(INFO)<<"找到param:  "<<key<<"="<<pairs->second;
		string *result =  new string(pairs->second);
		LOG(INFO)<<"getParamValue *result="<<*result;
		return result;
	}
}

vector<string>* ParamUtil::getParamValueList(const string &key,const string &delims){
	if(!paramMultimap){
		paramMultimap.reset(this->getParamMultimap(delims));
	}
	pair<unordered_map<string,string>::const_iterator, unordered_map<string,string>::const_iterator> range = paramMultimap->equal_range(key);

	if(range.first == range.second){
		LOG(INFO)<<"未找到 param value of key:"<<key;
		return nullptr;
	}else{
		vector<string>* result = new vector<string>();
		for(auto iter=range.first;iter!=range.second;++iter){
			LOG(INFO)<<"找到param:  "<<key<<"="<<iter->second;
			result->insert(result->begin(),iter->second);
		}
		return result;
	}
}


RequestParam::RequestParam(){
	char * method = NULL;
	//获取HTTP请求方法(POST/GET)
	if(NULL == (method = getenv("REQUEST_METHOD")))
	{
		LOG(ERROR)<<"未发现请求方法！";
		return;
	}


	if(getenv("CONTENT_LENGTH") && strcmp(method,"POST") == 0)
	{
		//POST 方法解析,从 STDIN_FILENO 动态获取数据
		int	n = atoi(getenv("CONTENT_LENGTH"));
		size_t length = n * sizeof(char) + 1;
		char * inputdata = (char *)malloc(length);
		if(inputdata)
		{
			memset((void*)inputdata,0,length);
			int read_num = read(STDIN_FILENO,inputdata,n);
			if(n != read_num)
			{
				LOG(ERROR)<<"读取post参数不完整"<<"CONTENT_LENGTH="<<n<<"    read_num="<<read_num;
			}

			this->requestParam = inputdata;

			LOG(INFO)<<"post data:"<<this->requestParam;

			free(inputdata);
		}
	}
	else if(getenv("QUERY_STRING") && strcmp(method,"GET") == 0)
	{
		this->requestParam = getenv("QUERY_STRING");
	}

	// 初始化paramUtil指针
	this->paramUtil.reset(new ParamUtil(this->requestParam));
}


string* RequestParam::getRequestValue(const string &key){
	return this->paramUtil->getParamValue(key,"&");
}

vector<string>* RequestParam::getRequestValueList(const string &key){
	return this->paramUtil->getParamValueList(key,"&");
}

