#ifndef CMD_MAP_H
#define CMD_MAP_H

#include <vector>
#include <iosfwd>
#include <functional>
#include <string>
#include <map>
#include "Polygon.h"

namespace flusova {
  struct CMDmap {
  public:

    explicit CMDmap(std::istream& in, std::ostream& out) : in_(in), out_(out), amount_(0){}

    void inputShapes(std::istream& in);
    void doArea();
    void doMax();
    void doMin();
    void doCount();
    void doRects();
    void doSame();

    Polygon same_;
    std::istream& in_;
    std::ostream& out_;
    std::size_t amount_;
    std::vector< Polygon > shapes_;

  };

  double getAreaOddEven(std::vector< Polygon >&, bool flag);
  double getAreaMean(std::vector< Polygon >&);
  double getAreaNum(int, std::vector< Polygon >&);
  double getMaxArea(std::vector< Polygon >&);
  double getMinArea(std::vector< Polygon >&);
  std::size_t getMaxVertexes(std::vector< Polygon >&);
  std::size_t getMinVertexes(std::vector< Polygon >&);
  std::size_t countEven(std::vector< Polygon >&);
  std::size_t countOdd(std::vector< Polygon >&);
  std::size_t countNum(int, std::vector< Polygon >&);

}

#endif
