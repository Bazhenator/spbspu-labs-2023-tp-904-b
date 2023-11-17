#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iosfwd>
#include <string>
#include <numeric>
#include "Commands.h"
#include "IOFmtGuard.h"

Commands::Commands(std::ostream& out, std::istream& in, std::vector< Polygon > shapes):
  out_(out),
  in_(in),
  shapes_(shapes)
{}

void Commands::getArea()
{
  Iofmtguard guard(out_);
  std::string parametr;
  in_ >> parametr;
  if (parametr == "EVEN")
  {
    double area = areaEven(shapes_);
    out_ << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (parametr == "ODD")
  {
    double area = areaOdd(shapes_);
    out_ << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (parametr == "MEAN")
  {
    if (shapes_.size() != 0)
    {
      double area = areaMean(shapes_);
      out_ << std::fixed << std::setprecision(1) << (area / shapes_.size()) << '\n';
    }
    else
    {
      getInvalidMessage(out_);
      return;
    }
  }
  else if (std::all_of(parametr.begin(), parametr.end(), ::isdigit))
  {
    size_t numberOfPoints = std::stoi(parametr);
    if (numberOfPoints < 3)
    {
      getInvalidMessage(out_);
      return;
    }
    else
    {
      double area = areaNum(numberOfPoints, shapes_);
      out_ << std::fixed << std::setprecision(1) << area << '\n';
    }
  }
  else
  {
    getInvalidMessage(out_);
    return;
  }
}

void Commands::getMax()
{
  Iofmtguard guard(out_);
  std::string parametr;
  in_ >> parametr;
  if (parametr == "AREA")
  {
    if (shapes_.size() != 0)
    {
      double maxArea = getMaxArea(shapes_);
      out_ << std::fixed << std::setprecision(1) << maxArea << '\n';
    }
    else
    {
      getInvalidMessage(out_);
      return;
    }
  }
  else if (parametr == "VERTEXES")
  {
    if (shapes_.size() != 0)
    {
      size_t maxPoints = getMaxVertexes(shapes_);
      out_ << maxPoints << '\n';
    }
    else
    {
      getInvalidMessage(out_);
      return;
    }
  }
  else
  {
    getInvalidMessage(out_);
    return;
  }
}

void Commands::getMin()
{
  Iofmtguard guard(out_);
  std::string parametr;
  in_ >> parametr;
  if (parametr == "AREA")
  {
    if (shapes_.size() != 0)
    {
      double minArea = getMinArea(shapes_);
      out_ << std::fixed << std::setprecision(1) << minArea << '\n';
    }
    else
    {
      getInvalidMessage(out_);
      return;
    }
  }
  else if (parametr == "VERTEXES")
  {
    if (shapes_.size() != 0)
    {
      size_t minPoints = getMinVertexes(shapes_);
      out_ << minPoints << '\n';
    }
    else
    {
      getInvalidMessage(out_);
      return;
    }
  }
  else
  {
    getInvalidMessage(out_);
    return;
  }
}

void Commands::countNumberOfShapes()
{
  Iofmtguard guard(out_);
  std::string parametr;
  in_ >> parametr;
  if (parametr == "EVEN")
  {
    size_t numberOfShapes = 0;
    numberOfShapes = getEvenCount(shapes_);
    out_ << numberOfShapes << '\n';
  }
  else if (parametr == "ODD")
  {
    size_t numberOfShapes = 0;
    numberOfShapes = getOddCount(shapes_);
    out_ << numberOfShapes << '\n';
  }
  else if (std::all_of(parametr.begin(), parametr.end(), ::isdigit))
  {
    size_t numberOfShapes = 0;
    size_t numberOfPoints = std::stoi(parametr);
    if (numberOfPoints < 3)
    {
      getInvalidMessage(out_);
      return;
    }
    else
    {
      numberOfShapes = getNumCount(numberOfPoints, shapes_);
      out_ << numberOfShapes << '\n';
    }
  }
  else
  {
    getInvalidMessage(out_);
    return;
  }
}

void Commands::getLessArea()
{
  Iofmtguard guard(out_);
  Polygon controlPolygon;
  in_ >> controlPolygon;
  if (!in_)
  {
    getInvalidMessage(out_);
    return;
  }
  else if (shapes_.size() != 0)
  {
    double controlArea = getPolygonArea(controlPolygon);
    size_t lessShapes = 0;
    if (in_)
    {
      lessShapes = std::accumulate(
        shapes_.begin(),
        shapes_.end(),
        0,
        [&controlArea](double a, const Polygon& polygon)
        {
          return (controlArea > getPolygonArea(polygon)) ? ++a : a;
        }
      );
    }
    out_ << lessShapes << '\n';
  }
  else
    out_ << "0";
}

void Commands::getRightShapes()
{
  Iofmtguard guard(out_);
  if (shapes_.size() != 0)
  {
    std::size_t rightShapes = 0;
    rightShapes = std::accumulate(
      shapes_.begin(),
      shapes_.end(),
      0,
      [](double a, const Polygon& polygon)
      {
        return isRightPolygon(polygon) ? ++a : a;
      }
    );
    out_ << rightShapes << '\n';
  }
  else
    out_ << "Empty";
}

double areaOdd(std::vector<Polygon>& shapes)
{
  double area = 0.0;
  if (shapes.size() != 0)
  {
    area = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0.0,
      [](double a, const Polygon& polygon)
      {
        return polygon.points_.size() % 2 != 0 ? a + getPolygonArea(polygon) : a;
      });
  }
  return area;
}

double areaEven(std::vector<Polygon>& shapes)
{
  double area = 0.0;
  if (shapes.size() != 0)
  {
    area = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0.0,
      [](double a, const Polygon& polygon)
      {
        return polygon.points_.size() % 2 == 0 ? a + getPolygonArea(polygon) : a;
      });
  }
  return area;
}

double areaMean(std::vector<Polygon>& shapes)
{
  double area = 0.0;
  area = std::accumulate(
    shapes.begin(),
    shapes.end(),
    0.0,
    [](double a, const Polygon& polygon)
    {
      return a + getPolygonArea(polygon);
    });
  return area;
}

double areaNum(size_t& vert, std::vector<Polygon>& shapes)
{
  double area = 0.0;
  if (shapes.size() != 0)
  {
    area = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0.0,
      [&vert](double a, const Polygon& polygon)
      {
        return polygon.points_.size() == vert ? a + getPolygonArea(polygon) : a;
      });
  }
  return area;
}

double getMinArea(std::vector<Polygon>& shapes)
{
  return getPolygonArea(*std::min_element(
    shapes.begin(),
    shapes.end(),
    [](const Polygon& left, const Polygon& right)
    {
      return getPolygonArea(left) < getPolygonArea(right);
    }));
}

size_t getMinVertexes(std::vector<Polygon>& shapes)
{
  return  std::min_element(
    shapes.begin(),
    shapes.end(),
    [](const Polygon& left, const Polygon& right)
    {
      return left.points_.size() < right.points_.size();
    })->points_.size();
}

double getMaxArea(std::vector<Polygon>& shapes)
{
  return getPolygonArea(*std::max_element(
    shapes.begin(),
    shapes.end(),
    [](const Polygon& left, const Polygon& right)
    {
      return getPolygonArea(left) < getPolygonArea(right);
    }));
}

size_t getMaxVertexes(std::vector<Polygon>& shapes)
{
  return std::max_element(
    shapes.begin(),
    shapes.end(),
    [](const Polygon& left, const Polygon& right)
    {
      return left.points_.size() < right.points_.size();
    })->points_.size();
}

size_t getEvenCount(std::vector<Polygon>& shapes)
{
  size_t numberOfShapes = 0;
  if (shapes.size() != 0)
  {
    numberOfShapes = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0,
      [](double a, const Polygon& polygon)
      {
        return polygon.points_.size() % 2 == 0 ? ++a : a;
      });
  }
  return numberOfShapes;
}

size_t getOddCount(std::vector<Polygon>& shapes)
{
  size_t numberOfShapes = 0;
  if (shapes.size() != 0)
  {
    numberOfShapes = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0,
      [](double a, const Polygon& polygon)
      {
        return polygon.points_.size() % 2 != 0 ? ++a : a;
      });
  }
  return numberOfShapes;
}

size_t getNumCount(size_t& vert, std::vector<Polygon>& shapes)
{
  size_t numberOfShapes = 0;
  if (shapes.size() != 0)
  {
    numberOfShapes = std::accumulate(
      shapes.begin(),
      shapes.end(),
      0,
      [&vert](double a, const Polygon& polygon)
      {
        return polygon.points_.size() % vert == 0 ? ++a : a;
      });
  }
  return numberOfShapes;
}

void getInvalidMessage(std::ostream& out)
{
  out << "<INVALID COMMAND>" << '\n';
}
