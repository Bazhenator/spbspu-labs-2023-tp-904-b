#ifndef POLYGON_H
#define POLYGON_H

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

namespace flusova {
  struct Point {
    int x, y;
    bool operator==(const Point& equal) const;
  };

  struct Polygon {
    void sortPoints(Polygon& same);
    void clear() ;
    double getVectLength(const Point&, const Point&);
    int getLeftPoint();
    double getCos(Point&, Point&, Point&);
    bool isRect();
    bool isSame(Polygon& same);
    double getArea();

    int peaks_;
    std::vector< Point > points_;
  };

  std::istream &operator>>(std::istream& in, Point& point);
  std::istream &operator>>(std::istream& in, Polygon& polygon);
}

#endif
