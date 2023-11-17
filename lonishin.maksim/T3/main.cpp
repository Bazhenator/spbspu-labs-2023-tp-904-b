#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
#include "Polygon.h"
#include "CommandHelper.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Error!\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "File doesn't exist\n";
    return 1;
  }
  try {
    std::vector<lonishin::Polygon> plane;
    while (!in.eof()) {
      in.clear();
      try {
        std::copy(
          std::istream_iterator<lonishin::Polygon>(in),
          std::istream_iterator<lonishin::Polygon>(),
          std::back_inserter(plane)
        );
      } catch (...) {}
    }
    in.close();
    lonishin::CommandHelper command(plane, std::cout);
    std::map< std::string, std::function< void() > > actions = {
      {"AREA", std::bind(&lonishin::CommandHelper::runCommandArea, std::ref(command), std::ref(std::cin))},
      {"MIN", std::bind(&lonishin::CommandHelper::runCommandMin, std::ref(command), std::ref(std::cin))},
      {"MAX", std::bind(&lonishin::CommandHelper::runCommandMax, std::ref(command), std::ref(std::cin))},
      {"COUNT", std::bind(&lonishin::CommandHelper::runCommandCount, std::ref(command), std::ref(std::cin))},
      {"INFRAME", std::bind(&lonishin::CommandHelper::runCommandInFrame, std::ref(command), std::ref(std::cin))},
      {"MASXEQ", std::bind(&lonishin::CommandHelper::runCommandMaxSeq, std::ref(command), std::ref(std::cin))}
    };
    std::string action;
    while (!std::cin.eof()) {
      std::istream::sentry sentry(std::cin);
      if (!sentry) {
        break;
      }
      std::cin >> action;
      auto result = actions.find(action);
      if (result == actions.end()) {
        if (!action.empty()) {
          lonishin::invalidMessage(std::cout, std::cin);
        }
        continue;
      }
      result->second();
    }
  } catch (const std::exception& error) {
    lonishin::invalidMessage(std::cout, std::cin);
  }
  return 0;
}
