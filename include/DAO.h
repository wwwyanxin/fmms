#ifndef DAO_H
#define DAO_H

#include "DBConn.h"
#include "Model.h"
#include <vector>
#include <string>
#include <glog/logging.h>

namespace wyx{
	using namespace std;

	class MemberDAO{
		public:
			void add(Member *member);
			void update(Member *member);
			Member* get(int &id);
			Member* get(string &account);
			Member* get(string &account,string &password);
			vector<shared_ptr<Member>>* list();
	};

	class ManagerDAO{
		public:
			Manager* get(string &account,string &password);
	};
}




#endif
