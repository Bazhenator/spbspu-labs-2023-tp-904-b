#include "Commands.h"
#include <iosfwd>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <string>
#include <numeric>
#include <iofmtquard.h>
#include "Polygon.h"

nedorezov::Commands::Commands(std::vector<nedorezov::Polygon> data, std::istream &in, std::ostream &out):
  data_(std::move(data)),
  in_(in),
  out_(out)
{}

void nedorezov::Commands::getArea()
{
  std::string command;
  in_ >> command;
  nedorezov::iofmtguard fmtguard(out_);

  if (command == "EVEN") {
    double sumOfAreas = std::accumulate(
            data_.begin(),
            data_.end(),
            0.0,
            [](double a, const Polygon &polygon)
            { return polygon.vertexes_ % 2 == 0 ? a + polygon.getArea() : a; }
    );
    out_ << std::fixed << std::setprecision(1) << sumOfAreas << '\n';
  } else if (command == "ODD") {
    double sumOfAreas = std::accumulate(
            data_.begin(),
            data_.end(),
            0.0,
            [](double a, const Polygon &polygon)
            { return polygon.vertexes_ % 2 != 0 ? a + polygon.getArea() : a; }
    );
    out_ << std::fixed << std::setprecision(1) << sumOfAreas << '\n';
  } else if (command == "MEAN") {
    if (data_.empty()) {
      executeInvalid();
      return;
    }
    double sumOfAreas = std::accumulate(
            data_.begin(),
            data_.end(),
            0.0,
            [](double a, const Polygon &polygon) { return a + polygon.getArea(); }
    );
    sumOfAreas /= data_.size();
    out_ << std::fixed << std::setprecision(1) << sumOfAreas << '\n';
  } else if (std::all_of(command.begin(), command.end(), ::isdigit)) {
    std::size_t numberOfVertexes = stoi(command);
    if (numberOfVertexes < 3) {
      executeInvalid();
      return;
    }
    double sumOfAreas = std::accumulate(
            data_.begin(),
            data_.end(),
            0.0,
            [numberOfVertexes](double a, const Polygon &polygon) {
              return polygon.vertexes_ == numberOfVertexes ? a + polygon.getArea() : a;
            }
    );
    out_ << std::fixed << std::setprecision(1) << sumOfAreas << '\n';
  } else {
    executeInvalid();
  }
}

void nedorezov::Commands::findMin()
{
  if (data_.empty()) {
    executeInvalid();
    return;
  }
  std::string command;
  in_ >> command;
  nedorezov::iofmtguard fmtguard(out_);
  if (command == "AREA") {
    double minArea = 0.0;
    if (!data_.empty()) {
      minArea = std::min_element(
              data_.begin(),
              data_.end(),
              [](const nedorezov::Polygon &left, const nedorezov::Polygon &right) {
                return left.getArea() < right.getArea();
              }
      )->getArea();
    }
    out_ << std::fixed << std::setprecision(1) << minArea << '\n';
  } else if (command == "VERTEXES") {
    int minVertexes = std::min_element(
            data_.begin(),
            data_.end(),
            [](const nedorezov::Polygon &left, const nedorezov::Polygon &right) {
              return left.vertexes_ < right.vertexes_;
            }
    )->vertexes_;
    out_ << minVertexes << '\n';
  } else {
    executeInvalid();
  }
}

void nedorezov::Commands::findMax()
{
  if (data_.empty()) {
    executeInvalid();
    return;
  }
  std::string command;
  in_ >> command;
  nedorezov::iofmtguard fmtguard(out_);
  if (command == "AREA") {
    double maxArea = 0.0;
    if (!data_.empty()) {
      maxArea = std::max_element(
              data_.begin(),
              data_.end(),
              [](const nedorezov::Polygon &left, const nedorezov::Polygon &right) {
                return left.getArea() < right.getArea();
              }
      )->getArea();
    }
    out_ << std::fixed << std::setprecision(1) << maxArea << '\n';
  } else if (command == "VERTEXES") {
    int maxVertexes = std::max_element(
            data_.begin(),
            data_.end(),
            [](const nedorezov::Polygon &left, const nedorezov::Polygon &right) {
              return left.vertexes_ < right.vertexes_;
            }
    )->vertexes_;
    out_ << maxVertexes << '\n';
  } else {
    executeInvalid();
  }
}

void nedorezov::Commands::count()
{
  std::string command;
  in_ >> command;
  nedorezov::iofmtguard fmtguard(out_);
  if (command == "EVEN") {
    int numberOfVertexes = std::count_if(
            data_.begin(),
            data_.end(),
            [](const Polygon &polygon) { return polygon.vertexes_ % 2 == 0; }
    );
    out_ << numberOfVertexes << '\n';
  } else if (command == "ODD") {
    int numberOfVertexes = std::count_if(
            data_.begin(),
            data_.end(),
            [](const Polygon &polygon) { return polygon.vertexes_ % 2 != 0; }
    );
    out_ << numberOfVertexes << '\n';
  } else if (std::all_of(command.begin(), command.end(), ::isdigit)) {
    std::size_t vertexes = stoi(command);
    if (vertexes < 3) {
      executeInvalid();
      return;
    }
    int numberOfVertexes = std::count_if(
            data_.begin(),
            data_.end(),
            [&vertexes](const Polygon &polygon) { return polygon.vertexes_ == vertexes; }
    );
    out_ << numberOfVertexes << '\n';
  } else {
    executeInvalid();
  }
}

void nedorezov::Commands::isSame()
{
  Polygon polygonSame{};
  nedorezov::iofmtguard fmtguard(out_);
  in_ >> polygonSame;
  if (!in_) {
    executeInvalid();
    return;
  }
  bool isSame = true;
  int samePolygons = 0;
  for (auto polygon: data_) {
    if (polygon.vertexes_ != polygonSame.vertexes_
        || polygon.getArea() != polygonSame.getArea()) {
      continue;
    }
    isSame = true;
    std::size_t polygonIndex = getMaxPointIndex(polygon);
    std::size_t polygonSameIndex = getMaxPointIndex(polygonSame);
    int currentDiffX = 0;
    int currentDiffY = 0;
    bool polygonSameDirection = (polygonSame.points_[0].x_ * polygonSame.points_[1].y_ -
                                 polygonSame.points_[0].y_ * polygonSame.points_[1].x_) >= 0;
    int prevDiffX = polygon.points_[polygonIndex].x_ - polygonSame.points_[polygonSameIndex].x_;
    int prevDiffY = polygon.points_[polygonIndex].y_ - polygonSame.points_[polygonSameIndex].y_;
    polygonIndex = (polygonIndex + 1 == polygon.vertexes_) ? 0 : polygonIndex + 1;
    if (polygonSameDirection) {
      polygonSameIndex = (polygonSameIndex + 1 == polygon.vertexes_) ? 0 : polygonSameIndex + 1;
    } else {
      polygonSameIndex = (polygonSameIndex == 0) ? polygon.vertexes_ : polygonSameIndex - 1;
    }

    for (std::size_t counter = 1; counter < polygon.vertexes_; counter++) {
      currentDiffX = polygon.points_[polygonIndex].x_ - polygonSame.points_[polygonSameIndex].x_;
      currentDiffY = polygon.points_[polygonIndex].y_ - polygonSame.points_[polygonSameIndex].y_;
      if (currentDiffX != prevDiffX || currentDiffY != prevDiffY) {
        isSame = false;
        break;
      }
      polygonIndex = (polygonIndex + 1 == polygon.vertexes_) ? 0 : polygonIndex + 1;
      if (polygonSameDirection) {
        polygonSameIndex = (polygonSameIndex + 1 == polygon.vertexes_) ? 0 : polygonSameIndex + 1;
      } else {
        polygonSameIndex = (polygonSameIndex == 0) ? polygon.vertexes_ : polygonSameIndex - 1;
      }
    }
    samePolygons += isSame;
  }
  out_ << samePolygons << '\n';
}

void nedorezov::Commands::isRightShapes()
{
  nedorezov::iofmtguard fmtguard(out_);
  if (data_.empty()) {
    executeInvalid();
    return;
  }
  int numberOfRightShapes = std::count_if(
          data_.begin(),
          data_.end(),
          [](const Polygon &polygon) { return isPolygonRightAngle(polygon); }
  );
  out_ << numberOfRightShapes << '\n';
}

void nedorezov::Commands::executeInvalid()
{
  nedorezov::iofmtguard fmtguard(out_);
  in_.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  in_.clear();
  out_ << "<INVALID COMMAND>" << '\n';
}
