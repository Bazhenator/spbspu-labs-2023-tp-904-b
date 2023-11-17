#ifndef OUTPUT_LITERALS_H
#define OUTPUT_LITERALS_H

#include <fstream>

namespace flusova {
  void printEmpty(std::ostream& out);
  void printInvalidCmd(std::ostream& out, std::istream& in);
}

#endif
