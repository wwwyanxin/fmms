#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <memory>

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

	class Coach{
		public:
			int id;
			string name;
			string sex;
			int entry_date;
			string introduction;
			string status; //在职on_work 离职off_work
	};

	class VenueType{
		public:
			int id;
			string type;
	};

	class Venue{
		public:
			int id;
			string name;
			int capacity;
			string status;
			shared_ptr<VenueType> venue_type;

			Venue();
	};
}





#endif
