#include "commands/compose.h"
#include "dip.h"
#include <string>

void dip::Compose::run(std::string params)
{
	std::string command = "docker-compose " + _files() + " " + _project_name() + " " + params;
	system(command.c_str());
}

std::string dip::Compose::_files()
{
	return _dip->dig(std::vector<std::string>{"compose", "files"}, " --file ");
}

std::string dip::Compose::_project_name()
{
	return _dip->dig(std::vector<std::string>{"compose", "project_name"}, " --project-name ");
}

dip::Compose::Compose(dip::Dip * dip)
{
	_dip = dip;
}