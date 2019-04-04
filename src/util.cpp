#include "../include/util.h"

using namespace std;
//using namespace wyx;

namespace wyx{


	vector<string>* string_split(const string& str, const string& delims){
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

	unordered_multimap<string,string>* getParamMultimap(const string &str,const string &delims){
		unordered_multimap<string,string> *result = new unordered_multimap<string,string>();
		shared_ptr<vector<string>> segment_list (string_split(str,delims));
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

	string* getParamValue(const string &str,const string &key,const string &delims){
		shared_ptr<unordered_multimap<string,string>> paramMultimap (getParamMultimap(str,delims));
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

	vector<string>* getParamValueList(const string &str,const string &key,const string &delims){
		shared_ptr<unordered_multimap<string,string>> paramMultimap (getParamMultimap(str,delims));
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

	string* getUrlValue(const string &key){
		return getParamValue(getenv("QUERY_STRING"),key,"&");
	}

	vector<string>* getUrlValueList(const string &key){
		return getParamValueList(getenv("QUERY_STRING"),key,"&");
	}
}
