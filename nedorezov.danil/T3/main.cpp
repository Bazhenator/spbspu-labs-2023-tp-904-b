#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <functional>

#include "Commands.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "!!Error!! Invalid number of CMD parameters" << '\n';
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "!!Error!! With open file!" << '\n';
    return 1;
  }
  std::vector< nedorezov::Polygon > shapes;
  while (!in.eof()) {
    in.clear();
    std::copy(
            std::istream_iterator< nedorezov::Polygon >(in),
            std::istream_iterator< nedorezov::Polygon >(),
            std::back_inserter(shapes)
    );
  }

  in.close();

  nedorezov::Commands commands(shapes, std::cin, std::cout);
  const std::map< std::string, std::function< void() > > commandMap ({
    {"AREA",std::bind(&nedorezov::Commands::getArea, std::ref(commands))},
    {"MIN",std::bind(&nedorezov::Commands::findMin, std::ref(commands))},
    {"MAX",std::bind(&nedorezov::Commands::findMax, std::ref(commands))},
    {"COUNT",std::bind(&nedorezov::Commands::count, std::ref(commands))},
    {"SAME",std::bind(&nedorezov::Commands::isSame, std::ref(commands))},
    {"RIGHTSHAPES",std::bind(&nedorezov::Commands::isRightShapes, std::ref(commands))}
  });
  std::string command;
  while (!std::cin.eof()) {
    command = "";
    std::cin >> command;
    auto it = commandMap.find(command);
    if (it == commandMap.end()){
      if (!command.empty()) {
        commands.executeInvalid();
      }
      continue;
    }
    it->second();
  }

  return 0;
}
