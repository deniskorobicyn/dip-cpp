#ifndef __H_COMPOSE__
#define __H_COMPOSE__
#include <string>

namespace dip {
	class Dip;

	class Compose {
		Dip* _dip;

		std::string _files();
		std::string _project_name();
	public:
		Compose(Dip*);
		void run(std::string);

	};
}
#endif // !__H_COMPOSE__
