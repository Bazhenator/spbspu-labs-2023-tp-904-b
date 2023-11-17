#include <map>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>
#include <vector>
#include "Commands.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid arguments of CMD" << '\n';
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error with file";
    return 1;
  }
  std::vector< Polygon > figures;
  while (!in.eof())
  {
   in.clear();
   std::copy(
    std::istream_iterator< Polygon >(in),
    std::istream_iterator< Polygon >(),
    std::back_inserter(figures)
   );
  }
  in.close();
  Commands inCommands(std::cout, std::cin, figures);
  const std::map< std::string, std::function< void() > > commandMap =
  {
    {"AREA", std::bind(&Commands::getArea, std::ref(inCommands))},
    {"MAX", std::bind(&Commands::getMax, std::ref(inCommands))},
    {"MIN", std::bind(&Commands::getMin, std::ref(inCommands))},
    {"COUNT", std::bind(&Commands::countNumberOfShapes, std::ref(inCommands))},
    {"LESSAREA", std::bind(&Commands::getLessArea, std::ref(inCommands))},
    {"RIGHTSHAPES", std::bind(&Commands::getRightShapes, std::ref(inCommands))}
  };
  std::string command = "";
  std::cin >> command;
  while (!std::cin.eof())
  {
    auto it = commandMap.find(command);
    if (it != commandMap.end())
    {
      it->second();
    }
    else
    {
      getInvalidMessage(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin.clear();
    std::cin >> command;
  }
  return 0;
}
