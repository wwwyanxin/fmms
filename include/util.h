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
	unordered_multimap<string,string>* getParamMultimap(const string &str,const string &delims);

	string* getParamValue(const string &str,const string &key,const string &delims);

	vector<string>* getParamValueList(const string &str,const string &key,const string &delims);

	string* getUrlValue(const string &key);

	vector<string>* getUrlValueList(const string &key);

}



#endif
