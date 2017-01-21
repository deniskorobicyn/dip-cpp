#ifndef __H_SERVICE__
#define __H_SERVICE__
#include <memory>
#include <string>

namespace dip {
	class Dip;
	class Arguments;
	class Service {
		Dip* _dip;
	public:
		Service(Dip*);
		void run(std::string, std::shared_ptr<Arguments>);
	};

}
#endif // !__H_SERVICE__
