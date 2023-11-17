#include "Polygon.h"

#include <cmath>
#include <algorithm>
#include <istream>
#include <iterator>

bool nedorezov::isRightAngle(Point p1, Point p2, Point p3)
{
  return ((p2.x_ - p1.x_) * (p3.x_ - p2.x_) + (p2.y_ - p1.y_) * (p3.y_ - p2.y_)) == 0;
}

double nedorezov::Polygon::getArea() const
{
  double temp = 0;
  for (std::size_t i = 0; i < points_.size() - 1; ++i) {
    temp += points_[i].x_ * points_[i + 1].y_;
    temp -= points_[i].y_ * points_[i + 1].x_;
  }
  temp = temp + points_[points_.size() - 1].x_ * points_[0].y_
         - points_[points_.size() - 1].y_ * points_[0].x_;
  temp = std::abs(temp);
  return temp / 2;
}

int nedorezov::getMaxPointIndex(const Polygon &polygon)
{
  Point maxPoint = polygon.points_[0];
  int maxPointIndex = 0;
  for (std::size_t i = 1; i < polygon.vertexes_; ++i) {
    if (polygon.points_[i].x_ > maxPoint.x_ && polygon.points_[i].y_ > maxPoint.y_) {
      maxPoint = polygon.points_[i];
      maxPointIndex = i;
    }
  }
  return maxPointIndex;
}

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  nedorezov::Polygon input;
  if (!(in >> input.vertexes_) || input.vertexes_ < 3) {
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    in.setstate(std::ios::failbit);
    return in;
  }
  Point point{};
  std::string pointsStr;
  std::string coordinateStr;
  std::getline(in, pointsStr);
  pointsStr.erase(0, 1);
  while (!pointsStr.empty()) {
    if (pointsStr[0] != '(' || pointsStr[pointsStr.length() - 1] != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    coordinateStr = pointsStr.substr(1, pointsStr.find(';') - 1);
    if (coordinateStr.empty() || std::find_if(coordinateStr.begin(),
                                              coordinateStr.end(),
                                              [](char c) { return !std::isdigit(c) && c != '-'; })
                                 != coordinateStr.end()) {
      in.setstate(std::ios::failbit);
      return in;
    }
    point.x_ = std::stoi(coordinateStr);
    coordinateStr = pointsStr.substr(pointsStr.find(';') + 1,
                                     pointsStr.find(')') - pointsStr.find(';') - 1);
    if (coordinateStr.empty() || std::find_if(coordinateStr.begin(),
                                              coordinateStr.end(),
                                              [](char c) { return !std::isdigit(c) && c != '-'; })
                                 != coordinateStr.end()) {
      in.setstate(std::ios::failbit);
      return in;
    }
    point.y_ = std::stoi(coordinateStr);
    input.points_.push_back(point);
    pointsStr.erase(0, pointsStr.find(')') + 2);
  }
  if (input.vertexes_ != input.points_.size()) {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest = input;
  return in;
}


bool nedorezov::isPolygonRightAngle(const Polygon &polygon)
{
  if (nedorezov::isRightAngle(polygon.points_[polygon.points_.size() - 2],
                              polygon.points_[polygon.points_.size() - 1],
                              polygon.points_[0])
      || nedorezov::isRightAngle(polygon.points_[polygon.points_.size() - 1],
                                 polygon.points_[0],
                                 polygon.points_[1])) {
    return true;
  }
  for (std::size_t i = 0; i < polygon.vertexes_ - 2; i++) {
    if (nedorezov::isRightAngle(polygon.points_[i], polygon.points_[i + 1], polygon.points_[i + 2])) {
      return true;
    }
  }
  return false;
}
