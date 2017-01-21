#ifndef __H_ENVIRONMENT__
#define __H_ENVIRONMENT__
#include <map>
#include <string>
namespace YAML {
	class Node;
}
namespace dip {
	class Environment {
		std::map<std::string, std::string> _env;
	public:
		Environment(YAML::Node*);

		std::string replace(std::string);
	};
}
#endif // !__H_ENVIRONMENT__
