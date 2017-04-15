#include <iostream>
#include <algorithm>

#include "dip.h"
#include "arguments.h"
#include "commands/compose.h"
#include "commands/service.h"
#include "commands/dnsdock.h"
#include "commands/ssh.h"
#include "environment.h"


using namespace dip;

Dip::Dip(std::shared_ptr<Arguments> args) : _loaded(false) {
	this->_args = args;
}

void Dip::execute() {
	switch (_command_code(_args->command_name())) {
	case dip::Dip::Code::SERVICE:
		_service();
		break;
	case dip::Dip::Code::PROVISION:
		_provision();
		break;
	case dip::Dip::Code::COMPOSE:
		_compose();
		break;
	case dip::Dip::Code::DNSDOCK:
		_dnsdock();
		break;
	case dip::Dip::Code::SSH:
		_ssh();
		break;
	case dip::Dip::Code::HELP:
	default:
		_show_help();
		break;
	}
}

void dip::Dip::_provision()
{
	if (!_loaded) _load_config();

	const YAML::Node provision_node = _root["provision"];

	if (!provision_node.IsSequence()) {
		std::cout << "Provision is invalid or empty!" << std::endl;
		return;
	}

	for (YAML::const_iterator it = provision_node.begin(); it != provision_node.end(); ++it) {
		std::string command = it->as<std::string>();

		std::cout << "Executing: " << command << std::endl;

		if (0 != system(_env->replace(command).c_str())) {
			std::cout << "Provision failed" << std::endl;
			break;
		}
	}
}
void dip::Dip::_service()
{
	Service s(this);
	s.run(_args->command_name(), _args);
}

void dip::Dip::_compose() {
	Compose c(this);
	c.run(_args->params());
}

void dip::Dip::_dnsdock() {
	Dnsdock dns(this);
	dns.run(_args->params());
}

void dip::Dip::_ssh() {
	Ssh ssh(this);
	std::string path = _args->params_at(1);
	if (path.empty()) {

#ifdef WIN32
		path = std::string(getenv("USERPROFILE")) + "/.ssh";
		std::replace(path.begin(), path.end(), '\\', '/');
#else
		path = std::string(getenv("HOME")) + "/.ssh/";
#endif
	}
	ssh.run(_args->params_at(0), path);
}

void dip::Dip::_show_help()
{
	std::cout <<
		"Docker Interaction Process (CPP version) \n"
		"Its a simple docker process runner. \n"
		"For full expirience it reqiured defined dip.yml. \n"
		"You can provide path to it by param --config \n"
		"   dip --config path/to/convig some command \n"
		""
		"Usage: \n"
		" - Compose \n"
		"   dip compose run some_service \n"
		" - Run \n"
		"   dip some_command_from_dip_yml \n"
		" - DNS may used without dip.yml \n"
		"   dip dns up \n"
		" - SSH may used without dip.yml \n"
		"   dip ssh add \n"
		"   dip ssh down \n"
		<< std::endl;
}

dip::Dip::Code dip::Dip::_command_code(std::string name) {
	if ("--help" == name || "help" == name) {
		return dip::Dip::Code::HELP;
	}
	else if ("provision" == name) {
		return dip::Dip::Code::PROVISION;
	}
	else if ("compose" == name) {
		return dip::Dip::Code::COMPOSE;
	}
	else if ("dns" == name) {
		return dip::Dip::Code::DNSDOCK;
	}
	else if ("ssh" == name) {
		return dip::Dip::Code::SSH;
	}
	else if (_commands_include(name)) {
		return dip::Dip::Code::SERVICE;
	}
	return dip::Dip::Code::UNKNOWN;
}
bool dip::Dip::_commands_include(std::string name)
{
	if (!_loaded) _load_config();
	const YAML::Node interactions_node = _root["interaction"];

	if (!interactions_node.IsMap()) {
		return false;
	}

	for (YAML::const_iterator it = interactions_node.begin(); it != interactions_node.end(); ++it)
		if (it->first.as<std::string>() == name)
			return true;

	return false;
}

void dip::Dip::_load_config()
{
	_root = YAML::LoadFile(_args->config_path());
	_env = std::make_shared<Environment>(&_root["environment"], _args->envp());
	_loaded = true;
}

std::string dip::Dip::dig(std::vector<std::string> keys, std::string prefix)
{
	if (!_loaded) _load_config();

	YAML::Node* node = &_root;
	for (auto it : keys)
		node = &((*node)[it]);

	std::string sequence_result = "";
	switch (node->Type()) {
	case YAML::NodeType::Scalar:
		return prefix + _env->replace(node->as<std::string>());
	case YAML::NodeType::Sequence:
		for (YAML::iterator it = node->begin(); it != node->end(); ++it) {
			sequence_result += prefix + _env->replace(it->as<std::string>());
		}
		return sequence_result;
	case YAML::NodeType::Null:
	case YAML::NodeType::Map:
	case YAML::NodeType::Undefined:
	default:
		return "";
	};
}

void dip::Dip::merge_env(std::string key, std::string value) {
	_env->set(key, value);
}

YAML::Node dip::Dip::operator[](std::string key)
{
	return _root[key];
}