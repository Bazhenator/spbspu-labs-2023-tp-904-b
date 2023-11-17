#ifndef BASE_SHAPES_H
#define BASE_SHAPES_H

#include <iosfwd>
#include <vector>

namespace ponomarev {
  struct Point {
    int x, y;
  };
  std::istream &operator>>(std::istream &in, Point &point);

  struct Polygon {
    double getArea() const;

    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Polygon &polygon);
}

#endif
