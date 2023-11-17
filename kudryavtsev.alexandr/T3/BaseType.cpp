#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <numeric>
#include "Structure.h"
#include "BaseType.h"

std::istream& operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t numberOfPoints = 0;
  in >> numberOfPoints >> std::ws;
  Polygon inPolygon;
  std::copy_if(
    std::istream_iterator< Point >(in),
    std::istream_iterator< Point >(),
    std::back_inserter(inPolygon.points_),
    [&in](const Point&)
    {
      if (in.peek() == '\n')
      {
        in.setstate(std::ios_base::eofbit);
      }
      return true;
    }
  );
  in.clear();
  in.ignore(256, '\n');
  if (numberOfPoints != inPolygon.points_.size() || inPolygon.points_.size() < 3)
  {
    in.setstate(std::ios_base::failbit);
  }
  if (in)
  {
    polygon = inPolygon;
  }
  return in;
}

double getPolygonArea(const Polygon& polygon)
{
double area = std::inner_product(
    polygon.points_.begin(), polygon.points_.end() - 1,
    polygon.points_.begin() + 1,
    0.0,
    std::plus< double >(),
    [](const Point& point1, const Point& point2)
    {
      return (point1.x_ - point2.x_) * (point1.y_ + point2.y_);
    });
  area += (polygon.points_[polygon.points_.size()-1].x_ - polygon.points_[0].x_) *
    (polygon.points_[polygon.points_.size() - 1].y_ + polygon.points_[0].y_);
  return std::abs(area) * 0.5;
}

bool isRightPolygon(const Polygon& polygon)
{
  for (std::size_t i = 0; i < polygon.points_.size()-2; i++)
  {
    if (((polygon.points_[i + 1].x_ - polygon.points_[i].x_)
      * (polygon.points_[i + 2].x_ - polygon.points_[i + 1].x_)
      + (polygon.points_[i + 1].y_ - polygon.points_[i].y_)
      * (polygon.points_[i + 2].y_ - polygon.points_[i + 1].y_)) == 0)
        return true;
  }
  if (((polygon.points_[polygon.points_.size() - 1].x_ - polygon.points_[polygon.points_.size() - 2].x_)
    * (polygon.points_[0].x_ - polygon.points_[polygon.points_.size() - 1].x_)
    + (polygon.points_[polygon.points_.size() - 1].y_ - polygon.points_[polygon.points_.size() - 2].y_)
    * (polygon.points_[0].y_ - polygon.points_[polygon.points_.size() - 1].y_))==0)
      return true;
  if (((polygon.points_[0].x_ - polygon.points_[polygon.points_.size() - 1].x_)
    * (polygon.points_[1].x_ - polygon.points_[0].x_)
    + (polygon.points_[0].y_ - polygon.points_[polygon.points_.size() - 1].y_)
    * (polygon.points_[1].y_ - polygon.points_[0].y_))==0)
      return true;
  return false;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimeterIO('(') >> point.x_ >> DelimeterIO(';') >> point.y_ >> DelimeterIO(')');
}
