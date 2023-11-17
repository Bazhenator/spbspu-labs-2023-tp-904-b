#include "Polygon.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

std::istream& lonishin::operator>>(std::istream& in, lonishin::Polygon& polygon) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::size_t amountOfPoint;
  in >> amountOfPoint;
  lonishin::Polygon temp;

  std::string data;
  std::getline(in >> std::ws, data);
  Point point{};
  while (!data.empty()) {
    if (data[0] != '(') {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    data.erase(0, 1);
    bool positiveX = true;
    if (data[0] == '-') {
      positiveX = false;
      data.erase(0, 1);
    }
    auto endX = std::find(data.begin(), data.end(), ';');
    if (endX == data.end() && !std::all_of(data.begin(), endX - 1, [](char sym) {
      return isdigit(sym);
    })) {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    std::size_t lengthX = std::distance(data.begin(), endX);
    if (lengthX == 0) {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    try {
      point.x_ = std::stoi(data.substr(0, lengthX));
    } catch (std::invalid_argument& e) {
      throw;
    } catch (std::out_of_range& e) {
      throw;
    }
    if (!positiveX) {
      point.x_ *= -1;
    }
    data.erase(0, lengthX + 1);
    bool positiveY = true;
    if (data[0] == '-') {
      positiveY = false;
      data.erase(0, 1);
    }
    auto endY = std::find(data.begin(), data.end(), ')');
    if (endX == data.end() && !std::all_of(data.begin(), endY - 1, [](char sym) {
      return isdigit(sym);
    })) {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    std::size_t lengthY = std::distance(data.begin(), endY);
    if (lengthY == 0) {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    try {
      point.y_ = std::stoi(data.substr(0, lengthY));
    } catch (std::invalid_argument& e) {
      throw;
    } catch (std::out_of_range& e) {
      throw;
    }
    if (!positiveY) {
      point.y_ *= -1;
    }
    data.erase(0, lengthY + 2);
    temp.points_.push_back(point);
  }
  if (amountOfPoint  != temp.points_.size() || temp.points_.size() < 3) {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if (in) {
    polygon = temp;
  }
  return in;
}

bool lonishin::operator==(lonishin::Polygon& first, lonishin::Polygon& second) {
  if (first.points_.size() != second.points_.size()) {
    return false;
  }
  return std::equal(first.points_.begin(), first.points_.end(), second.points_.begin());
}

int lonishin::minX(lonishin::Polygon& first)
{
  auto resultIt = std::min_element(first.points_.begin(), first.points_.end(), [] (Point& first, Point& second) {
    return (first.x_ < second.x_);
  });
  return resultIt->x_;
}

int lonishin::minY(lonishin::Polygon& first)
{
  auto resultIt = std::min_element(first.points_.begin(), first.points_.end(), [] (Point& first, Point& second) {
    return (first.y_ < second.y_);
  });
  return resultIt->y_;
}

int lonishin::maxX(lonishin::Polygon& first)
{
  auto resultIt = std::max_element(first.points_.begin(), first.points_.end(), [] (Point& first, Point& second) {
    return (first.x_ < second.x_);
  });
  return resultIt->x_;
}

int lonishin::maxY(lonishin::Polygon& first)
{
  auto resultIt = std::max_element(first.points_.begin(), first.points_.end(), [] (Point& first, Point& second) {
    return (first.y_ < second.y_);
  });
  return resultIt->y_;
}

double lonishin::Polygon::getArea() {
  std::size_t index = 0;
  double sum = std::accumulate(points_.begin(), points_.end(), 0, [&] (double acc, const Point& point) {
    index = (index + 1) % points_.size();
    return acc + (point.x_ * points_[index].y_) - (points_[index].x_ * point.y_);
  });
  return std::abs(sum * 0.5);
}

bool lonishin::operator==(lonishin::Point &first, lonishin::Point &second) {
  return (first.x_ == second.x_ && first.y_ == second.y_);
}

bool lonishin::operator!=(lonishin::Point &first, lonishin::Point &second) {
  return !(first == second);
}
