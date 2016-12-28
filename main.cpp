#include <iostream>
#include <yaml-cpp/yaml.h>


int main() {
  std::cout << "Hello, world!" << std::endl;
  YAML::Node node = YAML::Load("{name: Brewers, city: Milwaukee}");
  std::cout << node.size();
  return 0;
}