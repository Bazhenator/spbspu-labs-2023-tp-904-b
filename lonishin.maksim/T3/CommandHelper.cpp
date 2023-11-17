#include "CommandHelper.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <numeric>
#include <IOFormatGuard.h>

lonishin::CommandHelper::CommandHelper(std::vector< Polygon >& shapes, std::ostream& out) :
  shapes_(shapes),
  out_(out)
{}

void lonishin::CommandHelper::runCommandArea(std::istream& in)
{
  IOFormatGuard format(out_);
  std::string parameter;
  in >> parameter;
  if (parameter == "ODD") {
    out_ << std::fixed << std::setprecision(1) << areaOdd(shapes_) << '\n';
  } else if (parameter == "EVEN") {
    out_ << std::fixed << std::setprecision(1) << areaEven(shapes_) << '\n';
  } else if (parameter == "MEAN") {
    if (shapes_.empty()) {
      invalidMessage(out_, in);
    } else {
      out_ << std::fixed << std::setprecision(1) << areaMean(shapes_) << '\n';
    }
  } else if (std::all_of(parameter.begin(), parameter.end(), [](char sym) {
      return isdigit(sym);
    })) {
      std::size_t numberOfPoint = std::stoi(parameter);
      if (numberOfPoint < 3) {
        invalidMessage(out_, in);
      } else {
        out_ << std::fixed << std::setprecision(1) << areaNum(numberOfPoint, shapes_) << '\n';
      }
    } else {
    invalidMessage(out_, in);
  }
}

void lonishin::CommandHelper::runCommandMin(std::istream& in)
{
  IOFormatGuard format(out_);
  std::string parameter;
  in >> parameter;
  if (parameter == "AREA") {
    std::cout << std::fixed << std::setprecision(1) << areaMin(shapes_) << '\n';
  } else if (parameter == "VERTEXES") {
    std::cout <<  vertexMin(shapes_) << '\n';
  } else {
    invalidMessage(out_, in);
  }
}

void lonishin::CommandHelper::runCommandMax(std::istream& in)
{
  IOFormatGuard format(out_);
  std::string parameter;
  in >> parameter;
  if (parameter == "AREA") {
    if (shapes_.empty()) {
      invalidMessage(out_, in);
    } else {
      std::cout << std::fixed << std::setprecision(1) << areaMax(shapes_) << '\n';
    }
  } else if (parameter == "VERTEXES") {
    if (shapes_.empty()) {
      invalidMessage(out_, in);
    } else {
      std::cout << vertexMax(shapes_) << '\n';
    }
  } else {
    invalidMessage(out_, in);
  }
}

void lonishin::CommandHelper::runCommandCount(std::istream& in)
{
  IOFormatGuard format(out_);
  std::string parameter;
  in >> parameter;
  if (parameter == "EVEN") {
    std::cout << countEven(shapes_) << '\n';
  } else if (parameter == "ODD") {
    std::cout << countOdd(shapes_) << '\n';
  } else if (std::all_of(parameter.begin(), parameter.end(), [](char sym) {
    return isdigit(sym);
  })) {
    std::size_t numberOfPoint = std::stoi(parameter);
    if (numberOfPoint < 3) {
      invalidMessage(out_, in);
    } else {
      std::cout << countNum(numberOfPoint, shapes_) << '\n';
    }
  } else {
    invalidMessage(out_, in);
  }
}

void lonishin::CommandHelper::runCommandMaxSeq(std::istream& in)
{
  Polygon temp;
  std::cin >> temp;
  if (std::cin.fail()) {
    invalidMessage(out_, in);
  } else {
    int maxResult = 0;
    int result = 0;
    for (auto & shape : shapes_) {
      if (shape == temp) {
        ++result;
      } else {
        maxResult = (maxResult < result) ? result : maxResult;
        result = 0;
      }
    }
    std::cout << maxResult << '\n';
  }
}

void lonishin::CommandHelper::runCommandInFrame(std::istream& in)
{
  Polygon temp;
  std::cin >> temp;
  if (std::cin.fail()) {
    invalidMessage(out_, in);
  } else {
    auto xMinIterator = std::min_element(shapes_.begin(), shapes_.end(), [] (Polygon& first, Polygon& second) {
      return minX(first) < minX(second);
    });
    auto yMinIterator = std::min_element(shapes_.begin(), shapes_.end(), [] (Polygon& first, Polygon& second) {
      return minY(first) < minY(second);
    });
    auto xMaxIterator = std::max_element(shapes_.begin(), shapes_.end(), [] (Polygon& first, Polygon& second) {
      return maxX(first) < maxX(second);
    });
    auto yMaxIterator = std::max_element(shapes_.begin(), shapes_.end(), [] (Polygon& first, Polygon& second) {
      return maxY(first) < maxY(second);
    });
    int xMin = minX(*xMinIterator);
    int yMin = minY(*yMinIterator);
    int xMax = maxX(*xMaxIterator);
    int yMax = maxY(*yMaxIterator);
    auto b = std::find_if(temp.points_.begin(), temp.points_.end(), [&] (Point& point) {
      return !(point.x_ <= xMax && point.x_ >= xMin && point.y_ <= yMax && point.y_ >= yMin);
    });
    std::cout << ((b == temp.points_.end()) ? "<TRUE>\n" : "<FALSE>\n");
  }
}

std::ostream& lonishin::invalidMessage(std::ostream& out, std::istream& in)
{
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  in.clear();
  out << "<INVALID COMMAND>\n";
  return out;
}

double lonishin::areaOdd(std::vector< Polygon >& shapes)
{
  return std::accumulate(shapes.begin(), shapes.end(), 0.0, [](double sum, Polygon& polygon) {
    return (polygon.points_.size() % 2 != 0) ? sum + polygon.getArea() : sum;
  });
}

double lonishin::areaEven(std::vector< Polygon >& shapes)
{
  return std::accumulate(shapes.begin(), shapes.end(), 0.0, [](double sum, Polygon& polygon) {
    return (polygon.points_.size() % 2 == 0) ? sum + polygon.getArea() : sum;
  });
}

double lonishin::areaMean(std::vector< Polygon >& shapes)
{
  double area = std::accumulate(shapes.begin(), shapes.end(), 0.0, [](double sum, Polygon& polygon) {
    return sum + polygon.getArea();
  });
  return area / shapes.size();
}

double lonishin::areaNum(std::size_t target, std::vector< Polygon >& shapes)
{
  return std::accumulate(shapes.begin(), shapes.end(), 0.0, [&target](double sum, Polygon& polygon) {
    return (polygon.points_.size() == target) ? sum + polygon.getArea() : sum;
  });
}

double lonishin::areaMin(std::vector< Polygon >& shapes)
{
  auto minArea = std::min_element(shapes.begin(), shapes.end(), [&](Polygon& first, Polygon& second) {
    return first.getArea() < second.getArea();
  });
  return minArea->getArea();
}

double lonishin::areaMax(std::vector< Polygon >& shapes)
{
  auto maxArea = std::min_element(shapes.begin(), shapes.end(), [&](Polygon& first, Polygon& second) {
    return first.getArea() > second.getArea();
  });
  return maxArea->getArea();
}

std::size_t lonishin::vertexMin(std::vector< Polygon >& shapes)
{
  auto minVertexes = std::min_element(shapes.begin(), shapes.end(), [&](Polygon& first, Polygon& second) {
    return first.points_.size() < second.points_.size();
  });
  return minVertexes->points_.size();
}

std::size_t lonishin::vertexMax(std::vector< Polygon >& shapes)
{
  auto maxVertexes = std::min_element(shapes.begin(), shapes.end(), [&](Polygon& first, Polygon& second) {
    return first.points_.size() > second.points_.size();
  });
  return maxVertexes->points_.size();
}

std::size_t lonishin::countEven(std::vector< Polygon >& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(), [](Polygon& polygon) {
    return (polygon.points_.size() % 2 == 0);
  });
}

std::size_t lonishin::countOdd(std::vector< Polygon >& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(), [](Polygon& polygon) {
    return (polygon.points_.size() % 2 != 0);
  });
}

std::size_t lonishin::countNum(std::size_t target, std::vector< Polygon >& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(), [&target] (Polygon& polygon) {
    return (polygon.points_.size() == target);
  });
}
