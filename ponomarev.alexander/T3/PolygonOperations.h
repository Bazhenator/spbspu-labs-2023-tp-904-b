#ifndef POLYGON_OPERATIONS_H
#define POLYGON_OPERATIONS_H

#include <cstddef>
#include "BaseShapes.h"

namespace ponomarev {
  bool hasEvenSize(const Polygon &shape);
  bool hasOddSize(const Polygon &shape);
  bool hasNPoints(const Polygon &shape, std::size_t nPoints);
  bool isRectangle(const Polygon &shape);
  bool compareByArea(const Polygon &lhs, const Polygon &rhs);
  bool compareByVertexes(const Polygon &lhs, const Polygon &rhs);
  bool isRightAngle(Point a, Point b, Point c);
  Point getUpperBoundingPoint(const Polygon &polygon);
  Point getLowerBoundingPoint(const Polygon &polygon);
  bool isInBoundingRect(const Polygon &polygon, const Point &upperR, const Point &lowerL);
}

#endif
