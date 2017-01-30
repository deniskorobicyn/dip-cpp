#ifndef __H_SSH__
#define __H_SSHH__
#include <string>

namespace dip {
	class Dip;
	class Ssh {
		Dip* _dip;
	public:
		Ssh(Dip*);
		void run(std::string, std::string);
	};
}
#endif