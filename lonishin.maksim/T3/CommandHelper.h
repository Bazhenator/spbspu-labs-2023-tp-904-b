#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <vector>
#include "Polygon.h"

namespace lonishin {

  class CommandHelper
  {
  public:
    CommandHelper(std::vector< Polygon >& shapes, std::ostream& out);
    friend std::ostream& invalidMessage(std::ostream& out, std::istream& in);

    void runCommandArea(std::istream& in);
    void runCommandMin(std::istream& in);
    void runCommandMax(std::istream& in);
    void runCommandCount(std::istream& in);
    void runCommandInFrame(std::istream& in);
    void runCommandMaxSeq(std::istream& in);

  private:
    std::vector < Polygon > shapes_;
    std::ostream& out_;
  };

  double areaOdd(std::vector< Polygon >& shapes);
  double areaEven(std::vector< Polygon >& shapes);
  double areaMean(std::vector< Polygon >& shapes);
  double areaNum(std::size_t target, std::vector< Polygon >& shapes);
  double areaMin(std::vector< Polygon >& shapes);
  double areaMax(std::vector< Polygon >& shapes);
  std::size_t vertexMin(std::vector< Polygon >& shapes);
  std::size_t vertexMax(std::vector< Polygon >& shapes);
  std::size_t countEven(std::vector< Polygon >& shapes);
  std::size_t countOdd(std::vector< Polygon >& shapes);
  std::size_t countNum(std::size_t target, std::vector< Polygon >& shapes);


  std::ostream& invalidMessage(std::ostream& out, std::istream& in);
}

#endif
