#include <iostream>
#include <fstream>
#include "outputLiterals.h"
#include "CMDmap.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "invalid number of CMD parameters!" << '\n';
    return 1;
  } else {
    std::ifstream in;
    if (!in) {
      std::cerr << "Invalid stream!" << '\n';
    }
    in.open(argv[1]);
    flusova::CMDmap storage(std::cin, std::cout);
    const std::map< std::string, std::function< void() > > map ({
      {"AREA",std::bind(&flusova::CMDmap::doArea, std::ref(storage))},
      {"MIN",std::bind(&flusova::CMDmap::doMin, std::ref(storage))},
      {"MAX",std::bind(&flusova::CMDmap::doMax, std::ref(storage))},
      {"COUNT",std::bind(&flusova::CMDmap::doCount, std::ref(storage))},
      {"SAME",std::bind(&flusova::CMDmap::doSame, std::ref(storage))},
      {"RECTS",std::bind(&flusova::CMDmap::doRects, std::ref(storage))}
    });
    storage.inputShapes(in);
    while (!std::cin.eof()) {
      std::istream::sentry sentry(std::cin);
      if (!sentry) {
        continue;
      }
      std::string cmd;
      std::cin >> cmd;
      if (cmd == "SAME") {
        std::cin >> storage.same_;
        if (std::cin.rdstate() == std::ios_base::failbit) {
          flusova::printInvalidCmd(storage.out_, std::cin);
          std::cin.clear();
          continue;
        }
      }
      auto it = map.find(cmd);
      if (it != map.end()) {
        it->second();
      } else {
        flusova::printInvalidCmd(storage.out_, std::cin);
      }
    }
    return 0;
  }
}
