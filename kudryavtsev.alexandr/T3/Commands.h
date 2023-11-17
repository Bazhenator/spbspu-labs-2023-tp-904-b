#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "BaseType.h"

struct Commands
{
public:
  Commands(std::ostream& out, std::istream& in, std::vector< Polygon > shapes);
  void getArea();
  void getMax();
  void getMin();
  void countNumberOfShapes();
  void getLessArea();
  void getRightShapes();
private:
  std::ostream& out_;
  std::istream& in_;
  std::vector< Polygon > shapes_;
};

void getInvalidMessage(std::ostream& os);
double areaOdd(std::vector< Polygon >& shapes);
double areaEven(std::vector< Polygon >& shapes);
double areaMean(std::vector< Polygon >& shapes);
double areaNum(size_t& vert, std::vector< Polygon >& shapes);
double getMinArea(std::vector< Polygon >& shapes);
size_t getMinVertexes(std::vector< Polygon >& shapes);
double getMaxArea(std::vector< Polygon >& shapes);
size_t getMaxVertexes(std::vector< Polygon >& shapes);
size_t getEvenCount(std::vector< Polygon >& shapes);
size_t getOddCount(std::vector< Polygon >& shapes);
size_t getNumCount(size_t& vert, std::vector< Polygon >& shapes);
#endif
