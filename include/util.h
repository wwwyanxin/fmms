#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <glog/logging.h>  
#include <stdlib.h>
#include <memory>


namespace wyx{
	using namespace std;
	

	vector<string>* string_split(const string& str, const string& delims);

	class ParamUtil{
		private:
			shared_ptr<unordered_multimap<string,string>> paramMultimap;
			const string param;
		public:
			ParamUtil(const string &param);

			unordered_multimap<string,string>* getParamMultimap(const string &delims);

			string* getParamValue(const string &key,const string &delims);

			vector<string>* getParamValueList(const string &key,const string &delims);
	};
	class RequestParam{
		private:
			string requestParam;
			shared_ptr<ParamUtil> paramUtil;

		public:
			RequestParam();
			
			string* getRequestValue(const string &key);

			vector<string>* getRequestValueList(const string &key);
	};

	//unordered_multimap<string,string>* getParamMultimap(const string &str,const string &delims);

	///string* getParamValue(const string &str,const string &key,const string &delims);

	//vector<string>* getParamValueList(const string &str,const string &key,const string &delims);

	//string* getRequestValue(const string &key);

	//vector<string>* getRequestValueList(const string &key);

}



#endif
