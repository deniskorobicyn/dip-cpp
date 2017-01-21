#include "environment.h"
#include <yaml-cpp/yaml.h>
#include <stdlib.h>

dip::Environment::Environment(YAML::Node* env_node)
{
	for (YAML::const_iterator it = env_node->begin(); it != env_node->end(); ++it) {
		this->_env[it->first.as<std::string>()] = it->second.as<std::string>();
		_putenv((it->first.as<std::string>() + "=" + it->second.as<std::string>()).c_str());
	}
}

std::string dip::Environment::replace(std::string value)
{
	for (auto it : _env) {
		std::string from = "${" + it.first + "}";
		std::string to = it.second;
		size_t start_pos = value.find(from);
		if (start_pos == std::string::npos)
			continue;
		value.replace(start_pos, from.length(), to);
	}

	return value;
}