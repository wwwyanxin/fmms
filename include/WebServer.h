#ifndef WEB_SERVER_H
#define WEB_SERVER_H


#include <unordered_map>
#include <regex>
#include "Session.h"

namespace wyx{
	using namespace std;

	class WebServer{
		private: 

			shared_ptr<unordered_map<string,unordered_map<string,function<void()>>>>  resource;

			shared_ptr<wyx::Session> session;


		public:

			// 初始化从handler中获得resource
			void init();

			// 开始处理web请求
			void start();
	};
}






#endif
