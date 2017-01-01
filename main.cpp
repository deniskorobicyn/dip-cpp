#include <iostream>
#include <yaml-cpp/yaml.h>

int main() {
  std::cout << "Hello, world!" << std::endl;
  try {
	  YAML::Node config = YAML::LoadFile("dip.yml");
	  std::cout << config.size() << std::endl;
  }
  catch (YAML::BadFile e) {
	  std::cout << "File dip.yml is not found" << std::endl;
  }

  return 0;
}