#include "../include/util.h"
#include <unistd.h>
// linux转换编码
#include <codecvt>
#include <locale>

#include <assert.h>


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

std::string wyx::gb2312_to_utf8(std::string const &strGb2312)
{
	LOG(INFO)<<"gb to utf8";
	std::vector<wchar_t> buff(strGb2312.size());
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	wchar_t* pwszNext = nullptr;
	const char* pszNext = nullptr;
	mbstate_t state = {};
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).in(state,
				strGb2312.data(), strGb2312.data() + strGb2312.size(), pszNext,
				buff.data(), buff.data() + buff.size(), pwszNext);

	if (std::codecvt_base::ok == res)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
		return cutf8.to_bytes(std::wstring(buff.data(), pwszNext));

	}

	return "";


}

std::string wyx::utf8_to_gb2312(std::string const &strUtf8)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
	std::wstring wTemp = cutf8.from_bytes(strUtf8);
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	const wchar_t* pwszNext = nullptr;
	char* pszNext = nullptr;
	mbstate_t state = {};

	std::vector<char> buff(wTemp.size() * 2);
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).out(state,
				wTemp.data(), wTemp.data() + wTemp.size(), pwszNext,
				buff.data(), buff.data() + buff.size(), pszNext);

	if (std::codecvt_base::ok == res)
	{
		return std::string(buff.data(), pszNext);

	}
	return "";

}

unsigned char ToHex(unsigned char x) 
{ 
	return  x > 9 ? x + 55 : x + 48; 
}

unsigned char FromHex(unsigned char x) 
{ 
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else{
		LOG(ERROR)<<"FromHex ERROR";
		assert(0);
		y=' ';
	} 
	return y;
}

std::string wyx::UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) || 
				(str[i] == '-') ||
				(str[i] == '_') || 
				(str[i] == '.') || 
				(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);

		}

	}
	return strTemp;

}

std::string wyx::UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high*16 + low;

		}
		else strTemp += str[i];

	}
	return strTemp;

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
		string *result =  new string(pairs->second);
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
			for(int recv_count=0;recv_count<n;)
			{
				int read_num = read(STDIN_FILENO,inputdata+recv_count,n-recv_count);
				recv_count+=read_num;
			}
			/*
			memset((void*)inputdata,0,length);
			int read_num = read(STDIN_FILENO,inputdata,n);
			if(n != read_num)
			{
				LOG(ERROR)<<"读取post参数不完整"<<"CONTENT_LENGTH="<<n<<"    read_num="<<read_num;
			}
			*/

			this->requestParam = UrlDecode(inputdata);

			LOG(INFO)<<"post data:"<<this->requestParam;

			free(inputdata);
		}
	}
	else if(getenv("QUERY_STRING") && strcmp(method,"GET") == 0)
	{
		this->requestParam = UrlDecode(getenv("QUERY_STRING"));
	}

	// 初始化paramUtil指针
	this->paramUtil.reset(new ParamUtil(this->requestParam));
}


string RequestParam::getRequestValue(const string &key){
	shared_ptr<string> result(this->paramUtil->getParamValue(key,"&"));
	LOG(INFO)<<"getRequestValue: "<<key<<"="<<(result == nullptr ? "nullptr":"\""+*result+"\"");

	return result == nullptr ? "":*result;
}

vector<string>* RequestParam::getRequestValueList(const string &key){
	return this->paramUtil->getParamValueList(key,"&");
}

