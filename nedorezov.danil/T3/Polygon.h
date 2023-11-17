#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iosfwd>

namespace nedorezov {

  struct Point {
    int x_, y_;
  };

  bool isRightAngle(Point p1, Point p2, Point p3);

  struct Polygon {
    double getArea() const;
    std::vector< Point > points_;
    size_t vertexes_;
  };

  std::istream &operator>>(std::istream &in, Polygon &dest);

  int getMaxPointIndex(const Polygon &);
  bool isPolygonRightAngle(const Polygon &);

}
#endif
