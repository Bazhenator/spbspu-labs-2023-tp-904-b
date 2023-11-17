#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>

#include "Polygon.h"

namespace nedorezov {

  class Commands {
  public:
    Commands(std::vector< nedorezov::Polygon > data, std::istream &, std::ostream &out);
    void getArea();
    void findMin();
    void findMax();
    void count();
    void isSame();
    void isRightShapes();
    void executeInvalid();
  private:
    std::vector< Polygon > data_;
    std::istream &in_;
    std::ostream &out_;
  };

}
#endif
