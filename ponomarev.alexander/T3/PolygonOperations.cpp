#include "PolygonOperations.h"
#include <algorithm>
#include <numeric>

bool ponomarev::hasEvenSize(const Polygon &shape)
{
  return shape.points.size() % 2 == 0;
}
bool ponomarev::hasOddSize(const Polygon &shape)
{
  return shape.points.size() % 2 != 0;
}
bool ponomarev::hasNPoints(const Polygon &shape, std::size_t nPoints)
{
  return shape.points.size() == nPoints;
}
bool ponomarev::isRectangle(const Polygon &shape)
{
  return shape.points.size() == 4 &&
    isRightAngle(shape.points[0], shape.points[1], shape.points[2]) &&
    isRightAngle(shape.points[1], shape.points[2], shape.points[3]) &&
    isRightAngle(shape.points[2], shape.points[3], shape.points[0]);
}
bool ponomarev::compareByArea(const Polygon &lhs, const Polygon &rhs)
{
  return lhs.getArea() < rhs.getArea();
}
bool ponomarev::compareByVertexes(const Polygon &lhs, const Polygon &rhs)
{
  return lhs.points.size() < rhs.points.size();
}
bool ponomarev::isRightAngle(Point a, Point b, Point c)
{
  return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}
ponomarev::Point ponomarev::getUpperBoundingPoint(const Polygon &polygon)
{
  return std::accumulate(polygon.points.begin(), polygon.points.end(),
    polygon.points[0],
    [](const Point &init, const Point &next) {
      Point point;
      point.x = std::max(next.x, init.x);
      point.y = std::max(next.y, init.y);
      return point;
    });
}
ponomarev::Point ponomarev::getLowerBoundingPoint(const Polygon &polygon)
{
  return std::accumulate(polygon.points.begin(), polygon.points.end(),
    polygon.points[0],
    [](const Point &init, const Point &next) {
      Point point;
      point.x = std::min(next.x, init.x);
      point.y = std::min(next.y, init.y);
      return point;
    });
}
bool ponomarev::isInBoundingRect(const Polygon &polygon, const Point &upperR, const Point &lowerL)
{
  return std::all_of(polygon.points.begin(), polygon.points.end(),
    [&upperR, &lowerL](const Point &point) {
      return point.x <= upperR.x && point.x >= lowerL.x &&
        point.y >= lowerL.y && point.y <= upperR.y;
    });
}
