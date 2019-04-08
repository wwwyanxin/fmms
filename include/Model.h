#ifndef MODEL_H
#define MODEL_H

#include <string>

namespace wyx{
	using namespace std;
	class Member{
		public:
			int id;
			string account;
			string password;
			string name;
			string sex;
			int start_date;
			int end_date;
	};

	class Manager{
		public:
			int id;
			string account;
			string password;
	};
}





#endif
