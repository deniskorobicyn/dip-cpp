#include <iostream>
#include <stdio.h> /* defines FILENAME_MAX */
#include "yaml-cpp/yaml.h"


#include "arguments.h"
#include "dip.h"

using namespace dip;

int main(int argc, char **argv, char** envp) {

	Arguments args(argc, argv, envp);

	if (1 == args.parse()) {
		std::cout << args.error_message() << std::endl;
		return 1;
	}

	Dip dip(std::make_shared<Arguments>(args));

	try {
		dip.execute();
	} catch (YAML::BadFile e) {
		std::cout << "File dip.yml is not found" << std::endl;
	}

	return 0;
}