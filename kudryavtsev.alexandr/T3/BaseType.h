#ifndef BASETYPE_H
#define BASETYPE_H

#include <iosfwd>
#include <vector>

struct Point
{
  int x_, y_;
};

struct Polygon
{
  std::vector< Point > points_;
};

std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Polygon& polygon);
double getPolygonArea(const Polygon& polygon);
bool isRightPolygon(const Polygon& polygon);
#endif
