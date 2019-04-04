#ifndef HANDLER_H   
#define HANDLER_H

#include <unordered_map>
#include <functional>

namespace wyx{
	using namespace std;
	class Handler{
		private:
			static unordered_map<string,unordered_map<string,function<void ()>>>* webResource;
		public:
			static unordered_map<string,unordered_map<string,function<void ()>>>* getWebResource(){
				(*webResource)["^/test/?$"]["GET"]=[](){
					printf("Content-type:text/html; charset=utf-8\n\n"); //把后面要打印的信息输出到页面
					printf("Hello,World!!!<br>");
				};	
				return webResource;
			}
	};

}





#endif
