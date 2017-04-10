#include "commands/service.h"
#include "commands/compose.h"
#include "dip.h"
#include "arguments.h"
#include <iostream>


dip::Service::Service(Dip* dip)
{
	_dip = dip;
}

void dip::Service::run(std::string name, std::shared_ptr<Arguments> args)
{
	YAML::Node interation_node = (*_dip)["interaction"];

	YAML::Node service_node = interation_node[name];

	std::string service_name = "", service_command = "", service_args = "";
	if (service_node.IsMap()) {
		if (service_node["service"].IsScalar()) {
			service_name = service_node["service"].as<std::string>();
		}
		YAML::Node subcommands = service_node["subcommands"];
		if (subcommands.IsMap()) {
			std::string first_command = args->params_at(0);
			if (!first_command.empty()) {
				YAML::Node subcommand = subcommands[first_command];
				if (subcommand.IsMap()) {
					if (subcommand["service"].IsScalar()) {
						service_name = subcommand["service"].as<std::string>();
					}

					if (subcommand["command"].IsScalar()) {
						service_command = subcommand["command"].as<std::string>();
					}
				}
				service_args = args->params(1);
			}
		}
		else {
			if (service_node["service"].IsScalar()) {
				service_name = service_node["service"].as<std::string>();
			}
			if (service_node["command"].IsScalar()) {
				service_command = service_node["command"].as<std::string>();
			}
			service_args = args->params();
		}

		YAML::Node environment = service_node["environment"];
		if (environment.IsMap()) {
			for (YAML::const_iterator it = environment.begin(); it != environment.end(); ++it) {
				_dip->merge_env(it->first.as<std::string>(), it->second.as<std::string>());
			}
			
		}
	}

    std::string command = std::string("run --rm ") + service_name + " " + service_command + " " + service_args;
	dip::Compose compose(this->_dip);
	compose.run(command);
}