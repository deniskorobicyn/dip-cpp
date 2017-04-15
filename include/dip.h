#ifndef __H_DIP__
#define __H_DIP__
#include <vector>
#include <memory>
#include <string>
#include <yaml-cpp/yaml.h>

namespace dip {
	class Arguments;
	class Environment;
	class Dip {
	public:
		enum Code
		{
			SERVICE, PROVISION, HELP, COMPOSE, DNSDOCK, SSH, UNKNOWN
		};
	private:
		YAML::Node _root;
		std::shared_ptr<Arguments> _args;
		std::vector<std::string> _interaction_names;
		bool _loaded;
		std::shared_ptr<Environment> _env;

		void _provision();
		void _service();
		void _show_help();
		void _compose();
		void _dnsdock();
		void _ssh();


		void _load_config();
		Code _command_code(std::string);
		bool _commands_include(std::string);
	public:
		Dip(std::shared_ptr<Arguments>);
		YAML::Node operator[](std::string);

		void execute();

		void merge_env(std::string key, std::string value);
		std::string dig(std::vector<std::string> keys, std::string prefix);

	};
}
#endif // !__H_DIP__

