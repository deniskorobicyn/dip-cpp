#include "environment.h"
#include <yaml-cpp/yaml.h>
#include <stdlib.h>
#include <iostream>

dip::Environment::Environment(YAML::Node* env_node, char** env_system)
{
	for (YAML::const_iterator it = env_node->begin(); it != env_node->end(); ++it) {
		this->_env[it->first.as<std::string>()] = it->second.as<std::string>();
		_putenv((it->first.as<std::string>() + "=" + it->second.as<std::string>()).c_str());
	}

	for (char** env = env_system; *env != 0; env++)
	{
		std::string full_env(*env);
		int pos = full_env.find("=");
		this->_env[full_env.substr(0, pos)] = full_env.substr(pos + 1);
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

std::string dip::Environment::operator[](std::string key)
{
	return _env[key];
}

void dip::Environment::set(std::string key, std::string value) {
	_env[key] = value;
	_putenv((key + "=" + value).c_str());
}