#include "Polygon.h"
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>
#include "Separators.h"

bool flusova::Point::operator==(const Point& equal) const
{
  if ((this->x == equal.x) && (this->y == equal.y)) {
    return true;
  }
  return false;
}

void flusova::Polygon::sortPoints(flusova::Polygon& same) {
  int leftSame = same.getLeftPoint();
  int leftThis = this->getLeftPoint();
  auto itSame = std::find_if(same.points_.begin(), same.points_.end(), [leftSame](const Point& p) {
    return p.x == leftSame;
  });
  auto itThis = std::find_if(this->points_.begin(), this->points_.end(), [leftThis](const Point& p) {
    return p.x == leftThis;
  });
  if (itSame == same.points_.end() || itThis == this->points_.end())
    return;
  std::rotate(same.points_.begin(), itSame, same.points_.end());
  std::vector<Point> tempPoints(itThis, this->points_.end());
  tempPoints.insert(tempPoints.end(), this->points_.begin(), itThis);
  this->points_ = std::move(tempPoints);
}

void flusova::Polygon::clear() {
  points_.clear();
  peaks_ = 0;
}

double flusova::Polygon::getVectLength(const Point& p1, const Point& p2) {
  return std::sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int flusova::Polygon::getLeftPoint() {
  auto minPoint = std::min_element(points_.begin(), points_.end(), [](const Point& a, const Point& b) {
    return a.x < b.x;
  });
  return minPoint->x;
}

double flusova::Polygon::getCos(Point& p1, Point& p2, Point& p3) {
  return (((p1.x - p2.x) * (p2.x - p3.x)) + (p1.y - p2.y) * (p2.y - p3.y)) / (getVectLength(p1, p2) * getVectLength(p2, p3));
}

bool flusova::Polygon::isRect() {
  if (points_.empty()) {
    return false;
  }
  if (this->peaks_ == 4) {
    double cosAB = getCos(this->points_[0], this->points_[1], this->points_[2]);
    double cosCD = getCos(this->points_[0], this->points_[1], this->points_[2]);
    if (cosAB == 0 && cosCD == 0) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool flusova::Polygon::isSame(Polygon& same) {
  if (same.peaks_ != this->peaks_ || same.getArea() != this->getArea()) {
    return false;
  }
  this->sortPoints(same);
  std::vector< int > lengths(this->peaks_);
  std::transform(same.points_.begin(), same.points_.end(), this->points_.begin(), lengths.begin(), [this](const Point& p1, const Point& p2) {
    return static_cast< int >(this->getVectLength(p1, p2));
  });
  return std::adjacent_find(lengths.begin(), lengths.end(), std::not_equal_to< int >()) == lengths.end();
}

double flusova::Polygon::getArea() {
  std::vector< double > areas;
  std::vector < Point > copy = points_;
  copy.push_back(points_[0]);
  std::transform(copy.begin(), copy.end() - 1, copy.begin() + 1, std::back_inserter(areas),
    [](const Point& left, const Point& right)
    {
      double temp = (left.x + right.x) * (right.y - left.y);
      return temp;
    });
  double area = std::abs(0.5 * std::accumulate(areas.begin(), areas.end(), 0.0));
  return area;
}

std::istream& flusova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> Delimetr{ '(' } >> point.x >> Delimetr{ ';' } >> point.y >> Delimetr{ ')' };
}

std::istream& flusova::operator>>(std::istream& in, Polygon& polygon) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Polygon inputPolygon;
  size_t count;
  in >> count;
  std::copy_if(std::istream_iterator< Point >(in), std::istream_iterator< Point >(), std::back_inserter(inputPolygon.points_),
    [&in](const Point& point) {
    if ((in.eof()) || (in.peek() == '\n')) {
      in.setstate(std::ios_base::eofbit);
    }
    return (typeid(point.x) == typeid(int));
  });
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if ((count < 3) || (count != inputPolygon.points_.size())) {
    in.setstate(std::ios::failbit);
  } else {
    polygon.points_ = inputPolygon.points_;
    polygon.peaks_ = inputPolygon.points_.size();
  }
  return in;
}
