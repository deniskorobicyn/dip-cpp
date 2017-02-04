#include "arguments.h"
#include <stdio.h>
#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace dip;

Arguments::Arguments(int argc, char** argv, char** envp) {
	this->_argc = argc;
	this->_argv = argv;
	this->_envp = envp;
}

int Arguments::parse() {
	if (_argc < 2) {
		this->_command_name = "help";
		return 0;
	}

	int start_arg = 1;

	if (_argv[start_arg] == "--config") {
		++start_arg;
		if (_argc < start_arg) {
			this->_config_path = _argv[start_arg];
		}
		else {
			_error_message = "--config require path argument";
			return 1;
		}
	}
	else {
		char currentPath[FILENAME_MAX];
		if (!GetCurrentDir(currentPath, sizeof(currentPath))) {
			_error_message = "Current path is too long";

			return 1;
		}
		else {
			_config_path = std::string(currentPath) + "\\dip.yml";
		}

	}

	if (start_arg < _argc) {
		this->_command_name = _argv[start_arg];
		start_arg++;
	}
	else {
		_error_message = "Command is required";
		return 1;
	}

	this->_splited_params.resize(_argc - start_arg + 1);
	for (int i = start_arg; i < _argc; ++i) {
		this->_splited_params[i - start_arg] = std::string(_argv[i]);
	}

	return 0;
}

std::string dip::Arguments::command_name() const
{
	return _command_name;
}

std::string dip::Arguments::config_path() const
{
	return _config_path;
}

std::string dip::Arguments::params(int index) const
{
	std::string res = "";
	for (int i = index; i < _splited_params.size(); ++i) {
		res += _splited_params[i];
		res += " ";
	}
	return res;
}

std::string dip::Arguments::params_at(int index)
{
	if(index > this->_splited_params.size())
		return "";

	return this->_splited_params[index];
}

char** dip::Arguments::envp() {
	return this->_envp;
}

std::string dip::Arguments::error_message() const {
	return this->_error_message;
}