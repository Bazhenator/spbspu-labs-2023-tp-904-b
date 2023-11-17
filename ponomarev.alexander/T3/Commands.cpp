#include "Commands.h"
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <IOFormatGuard.h>

const std::map< std::string, std::function< bool(const ponomarev::Polygon &) > >
ponomarev::Commands::filters_ =
  {
    {"EVEN", hasEvenSize},
    {"ODD", hasOddSize},
    {"MEAN", [](const Polygon &shape) {
      return !shape.points.empty();
    }}
  };
const std::map< std::string, std::function< bool(const ponomarev::Polygon &, const ponomarev::Polygon &) > >
ponomarev::Commands::comparators_ =
  {
    {"AREA", compareByArea},
    {"VERTEXES", compareByVertexes}
  };

ponomarev::Commands::Commands(std::vector< Polygon > shapes, std::istream &is, std::ostream &os):
  shapes_(shapes),
  is_(is),
  os_(os)
{}
void ponomarev::Commands::computeArea()
{
  using namespace std::placeholders;

  std::string parameter;
  std::getline(is_ >> std::ws, parameter);
  auto it = filters_.find(parameter);
  bool isNumeric = std::all_of(parameter.begin(), parameter.end(),
    [](unsigned char c) {
      return std::isdigit(c);
    });
  if (it == filters_.end() && !isNumeric) {
    printInvalid(os_);
    return;
  }
  std::size_t nPoints = 0;
  if (isNumeric) {
    nPoints = std::stoull(parameter);
    if (nPoints < 3) {
      printInvalid(os_);
      return;
    }
  }

  auto filter = isNumeric ? std::bind(hasNPoints, _1, nPoints) : it->second;
  double area = std::accumulate(shapes_.begin(), shapes_.end(), 0.0,
    [&filter](double init, const Polygon &shape) {
      return (filter(shape) ? init + shape.getArea() : init);
    });

  if (!parameter.compare("MEAN")) {
    if (shapes_.empty()) {
      printInvalid(os_);
      return;
    }
    area /= shapes_.size();
  }
  IOFormatGuard guard(os_);
  os_ << std::fixed << std::setprecision(1);
  os_ << area;
  os_ << '\n';
}
void ponomarev::Commands::findMax()
{
  std::string parameter;
  std::getline(is_ >> std::ws, parameter);
  auto it = comparators_.find(parameter);
  if (it == comparators_.end()) {
    printInvalid(os_);
    return;
  }

  IOFormatGuard guard(os_);
  os_ << std::fixed << std::setprecision(1);
  auto polygonIt = std::max_element(shapes_.begin(), shapes_.end(), it->second);
  if (polygonIt == shapes_.end()) {
    printInvalid(os_);
    return;
  }
  if (parameter == "AREA") {
    os_ << polygonIt->getArea();
  } else {
    os_ << polygonIt->points.size();
  }
  os_ << '\n';
}
void ponomarev::Commands::findMin()
{
  std::string parameter;
  std::getline(is_ >> std::ws, parameter);
  auto it = comparators_.find(parameter);
  if (it == comparators_.end()) {
    printInvalid(os_);
    return;
  }

  IOFormatGuard guard(os_);
  os_ << std::fixed << std::setprecision(1);
  auto polygonIt = std::min_element(shapes_.begin(), shapes_.end(), it->second);
  if (polygonIt == shapes_.end()) {
    printInvalid(os_);
    return;
  }
  if (parameter == "AREA") {
    os_ << polygonIt->getArea();
  } else {
    os_ << polygonIt->points.size();
  }
  os_ << '\n';
}
void ponomarev::Commands::countShapes()
{
  using namespace std::placeholders;

  std::string parameter;
  std::getline(is_ >> std::ws, parameter);
  auto it = filters_.find(parameter);
  bool isNumeric = std::all_of(parameter.begin(), parameter.end(),
    [](unsigned char c) {
      return std::isdigit(c);
    });
  if (it == filters_.end() && !isNumeric) {
    printInvalid(os_);
    return;
  }
  std::size_t nPoints = 0;
  if (isNumeric) {
    nPoints = std::stoull(parameter);
    if (nPoints < 3) {
      printInvalid(os_);
      return;
    }
  }

  auto filter = isNumeric ? std::bind(hasNPoints, _1, nPoints) : it->second;
  os_ << std::count_if(shapes_.begin(), shapes_.end(), filter) << '\n';
}
void ponomarev::Commands::countRectangles()
{
  os_ << std::count_if(shapes_.begin(), shapes_.end(), isRectangle) << '\n';
}
void ponomarev::Commands::isInFrame()
{
  Polygon polygon;
  is_ >> polygon;
  if (is_.rdstate() == std::ios_base::failbit) {
    printInvalid(os_);
    return;
  }

  using namespace std::placeholders;
  auto findMax = [](const Point &init, const Polygon &polygon, std::function< Point(const Polygon&) > getPoint)
    {
      Point point = getPoint(polygon);
      point.x = std::max(point.x, init.x);
      point.y = std::max(point.y, init.y);
      return point;
    };
  auto findMin = [](const Point &init, const Polygon &polygon, std::function< Point(const Polygon&) > getPoint)
    {
      Point point = getPoint(polygon);
      point.x = std::min(point.x, init.x);
      point.y = std::min(point.y, init.y);
      return point;
    };
  Point upperRight = std::accumulate(shapes_.begin(), shapes_.end(),
    shapes_[0].points[0], std::bind(findMax, _1, _2, getUpperBoundingPoint));
  Point lowerLeft = std::accumulate(shapes_.begin(), shapes_.end(),
    shapes_[0].points[0], std::bind(findMin, _1, _2, getLowerBoundingPoint));
  os_ << (isInBoundingRect(polygon, upperRight, lowerLeft) ? "<TRUE>\n" : "<FALSE>\n");
}

void ponomarev::printInvalid(std::ostream &os)
{
  os << "<INVALID COMMAND>\n";
}
