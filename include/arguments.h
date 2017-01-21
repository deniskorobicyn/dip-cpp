#ifndef __ARGUMENTS__
#define __ARGUMENTS__
#include <string>
#include <vector>
#include <memory>

namespace dip {
	class Arguments {
	public:
		
	private:
		int _argc;
		char** _argv;
		std::vector<std::string> _splited_params;
		std::string _command_name;
		std::string _config_path;

	public:
		Arguments(int argc, char** argv);

		int parse();
		std::string command_name() const;
		std::string params(int index = 0) const;
		std::string config_path() const;
		std::string params_at(int);
	};
}
#endif // !__ARGUMENTS__
