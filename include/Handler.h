#ifndef HANDLER_H   
#define HANDLER_H

#include <unordered_map>
#include <functional>
#include <json/json.h>
#include <iostream>


namespace wyx{
	using namespace std;
	class Handler{
		private:
			static unordered_map<string,unordered_map<string,function<void ()>>>* webResource;
		public:
			static unordered_map<string,unordered_map<string,function<void ()>>>* getWebResource();

			static void response(Json::Value &JsonRoot,const bool &status=true);

			static void response(const string &text);

			static void response(const bool &status);

			static void redirect(const string &url);


	};

}





#endif
