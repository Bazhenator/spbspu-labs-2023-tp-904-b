#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <ios>

namespace lonishin {

  struct Point
  {
    int x_;
    int y_;
  };

  struct Polygon
  {
    double getArea();
    std::vector< Point > points_;
  };

  int minX(Polygon& first);
  int minY(Polygon& first);
  int maxX(Polygon& first);
  int maxY(Polygon& first);
  bool operator==(Polygon& first, Polygon& second);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(Point& first, Point& second);
  bool operator!=(Point& first, Point& second);
}

#endif
