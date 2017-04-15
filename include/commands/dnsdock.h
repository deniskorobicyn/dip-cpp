#ifndef __H_DNSDOCK__
#define __H_DNSDOCK__
#include <string>

namespace dip {
	class Dip;
	class Dnsdock {
		Dip* _dip;
	public:
		Dnsdock(Dip*);
		void run(std::string);
	};
}
#endif // !__H_SERVICE__