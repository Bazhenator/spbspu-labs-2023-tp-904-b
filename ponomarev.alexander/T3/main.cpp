#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "BaseShapes.h"
#include "Commands.h"

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "Error: CML args are not correct.\n";
    return 2;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "File couldn't be opened.\n";
    return 1;
  }

  std::vector< ponomarev::Polygon > data;
  while (!file.eof()) {
    file.clear();
    std::copy(
      std::istream_iterator< ponomarev::Polygon >(file),
      std::istream_iterator< ponomarev::Polygon >(),
      std::back_inserter(data)
    );
  }

  ponomarev::Commands commands(data, std::cin, std::cout);
  const std::map< std::string, std::function< void() > > commandsMap = {
    {"AREA", std::bind(&ponomarev::Commands::computeArea, std::ref(commands))},
    {"MAX", std::bind(&ponomarev::Commands::findMax, std::ref(commands))},
    {"MIN", std::bind(&ponomarev::Commands::findMin, std::ref(commands))},
    {"COUNT", std::bind(&ponomarev::Commands::countShapes, std::ref(commands))},
    {"RECTS", std::bind(&ponomarev::Commands::countRectangles, std::ref(commands))},
    {"INFRAME", std::bind(&ponomarev::Commands::isInFrame, std::ref(commands))}
  };
  std::string command = "";
  while (!std::cin.eof()) {
    command = "";
    std::cin >> command;
    auto it = commandsMap.find(command);
    if (it == commandsMap.end()) {
      if (!command.empty()) {
        ponomarev::printInvalid(std::cout);
      }
      std::cin.ignore(256, '\n');
      continue;
    }
    it->second();
    std::cin.clear();
  }
  return 0;
}
