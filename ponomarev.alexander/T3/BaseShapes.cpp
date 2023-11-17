#include "BaseShapes.h"
#include <iostream>
#include <UnitIO.h>
#include <algorithm>
#include <numeric>
#include <cstddef>
#include <string>
#include <iterator>

std::istream &ponomarev::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  return in >> DelimitersIO("(") >> point.x
    >> DelimitersIO(";") >> point.y >> DelimitersIO(")");
}

double ponomarev::Polygon::getArea() const
{
  std::vector< Point > pointsCopy = points;
  pointsCopy.push_back(points[0]);
  double area = std::inner_product(
    pointsCopy.begin(), pointsCopy.end() - 1,
    pointsCopy.begin() + 1,
    0.0,
    std::plus< double >(),
    [](const Point &p1, const Point &p2) {
      return (p1.x + p2.x) * (p1.y - p2.y);
    });
  return std::abs(area) * 0.5;
}
std::istream &ponomarev::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  std::size_t nPoints;
  in >> nPoints >> std::ws;

  Polygon newOne;
  std::copy_if(
    std::istream_iterator< Point >(in),
    std::istream_iterator< Point >(),
    std::back_inserter(newOne.points),
    [&in](const Point &point) {
      if (in.peek() == '\n') {
        in.setstate(std::ios_base::eofbit);
      }
      return point.x != 0.001;
    }
  );
  in.clear();
  in.ignore(256, '\n');
  if (nPoints != newOne.points.size() || newOne.points.size() < 3) {
    in.setstate(std::ios_base::failbit);
  }
  if (in.rdstate() != std::ios_base::failbit) {
    polygon = newOne;
  }
  return in;
}
