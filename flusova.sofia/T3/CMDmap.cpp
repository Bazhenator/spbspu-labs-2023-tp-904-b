#include "CMDmap.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iomanip>

#include "Polygon.h"
#include "outputLiterals.h"
#include "iofmtguard.h"

void flusova::CMDmap::inputShapes(std::istream& in) {
  while (!in.eof()) {
    in.clear();
    std::copy(std::istream_iterator< Polygon >(in), std::istream_iterator< Polygon >(),
      std::back_inserter(shapes_));
  }
}

void flusova::CMDmap::doArea() {
  flusova::iofmtguard fmtguard(out_);
  std::string keyword;
  in_ >> keyword;
  if (keyword == "EVEN" || keyword == "ODD") {
    bool isEven = (keyword == "EVEN");
    out_ << std::fixed << std::setprecision(1) << getAreaOddEven(shapes_, isEven) << '\n';
  } else if (keyword == "MEAN") {
    if (shapes_.empty()) {
      flusova::printInvalidCmd(out_, in_);
      return;
    }
    out_ << std::fixed << std::setprecision(1) << getAreaMean(shapes_) / shapes_.size() << '\n';
  } else if (std::all_of(keyword.begin(), keyword.end(), [](char c) { return isdigit(c); })) {
    int count = std::stoi(keyword);
    if (count < 3) {
      flusova::printInvalidCmd(out_, in_);
      return;
    }
    out_ << std::fixed << std::setprecision(1) << getAreaNum(count, shapes_) << '\n';
  } else {
    flusova::printInvalidCmd(out_, in_);
  }
}

void flusova::CMDmap::doMax() {
  flusova::iofmtguard fmtguard(out_);
  std::string keyword;
  in_ >> keyword;
  if (shapes_.empty()) {
    flusova::printInvalidCmd(out_, in_);
    return;
  }
  if (keyword == "AREA") {
    out_ << std::fixed << std::setprecision(1) << getMaxArea(shapes_) << '\n';
  } else if (keyword == "VERTEXES") {
    out_ << std::fixed << std::setprecision(1) << getMaxVertexes(shapes_) << '\n';
  } else {
    flusova::printInvalidCmd(out_, in_);
  }
}

void flusova::CMDmap::doMin() {
  flusova::iofmtguard fmtguard(out_);
  std::string keyword;
  in_ >> keyword;
  if (shapes_.empty()) {
    flusova::printInvalidCmd(out_, in_);
    return;
  }
  if (keyword == "AREA") {
    out_ << std::fixed << std::setprecision(1) << getMinArea(shapes_) << '\n';
  } else if (keyword == "VERTEXES") {
    out_ << std::fixed << std::setprecision(1) << getMinVertexes(shapes_) << '\n';
  } else {
    flusova::printInvalidCmd(out_, in_);
  }
}

void flusova::CMDmap::doCount() {
  flusova::iofmtguard fmtguard(out_);
  std::string keyword;
  in_ >> keyword;
  if (keyword == "EVEN") {
    out_ << countEven(shapes_) << '\n';
  } else if (keyword == "ODD") {
    out_ << countOdd(shapes_) << '\n';
  } else if (std::all_of(keyword.begin(), keyword.end(), [](char c) { return isdigit(c); })) {
    int number = std::stoi(keyword);
    if (number < 3) {
      flusova::printInvalidCmd(out_, in_);
      return;
    }
    out_ << countNum(number, shapes_) << '\n';
  } else {
    flusova::printInvalidCmd(out_, in_);
  }
}

void flusova::CMDmap::doRects() {
  flusova::iofmtguard fmtguard(out_);
  amount_ = std::count_if(shapes_.begin(), shapes_.end(),
    [](Polygon& curShape) {
    return curShape.isRect();
  });
  out_ << amount_ << '\n';
}

void flusova::CMDmap::doSame() {
  flusova::iofmtguard fmtguard(out_);
  if (this->same_.peaks_ != 0) {
    amount_ = std::count_if(shapes_.begin(), shapes_.end(),
      [this](Polygon& curShape) {
      return curShape.isSame(this->same_);
    });
    out_ << amount_ << '\n';
    return;
  } else {
    flusova::printInvalidCmd(out_, in_);
  }
}

double flusova::getAreaOddEven(std::vector< flusova::Polygon >& shapes, bool flag) {
  return std::accumulate(shapes.begin(), shapes.end(), 0.0,
    [flag](double acc, flusova::Polygon& polygon) {
    return (polygon.peaks_ % 2 == 0) == flag ? acc + polygon.getArea() : acc;
  });
}

double flusova::getAreaMean(std::vector< flusova::Polygon >& shapes) {
  return std::accumulate(shapes.begin(), shapes.end(), 0.0,
    [](double acc, flusova::Polygon& polygon) {
    return acc + polygon.getArea();
  });
}

double flusova::getAreaNum(int count, std::vector< flusova::Polygon >& shapes) {
  return std::accumulate(shapes.begin(), shapes.end(), 0.0,
    [count](double acc, flusova::Polygon& polygon) {
    return polygon.peaks_ == count ? acc + polygon.getArea() : acc;
  });
}

double flusova::getMaxArea(std::vector< Polygon >& shapes) {
  auto result = std::max_element(shapes.begin(), shapes.end(),
    [](Polygon& p1, Polygon& p2) {
    return p1.getArea() < p2.getArea();
  });
  return result->getArea();
}

double flusova::getMinArea(std::vector< Polygon >& shapes) {
  auto result = std::min_element(shapes.begin(), shapes.end(),
    [](Polygon& p1, Polygon& p2) {
    return p1.getArea() < p2.getArea();
  });
  return result->getArea();
}

std::size_t flusova::getMaxVertexes(std::vector< Polygon >& shapes) {
  auto result = std::max_element(shapes.begin(), shapes.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.peaks_ < p2.peaks_;
  });
  return result->peaks_;
}

std::size_t flusova::getMinVertexes(std::vector< Polygon >& shapes) {
  auto result = std::min_element(shapes.begin(), shapes.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.peaks_ < p2.peaks_;
  });
  return result->peaks_;
}

std::size_t flusova::countEven(std::vector< Polygon >& shapes) {
  return std::count_if(shapes.begin(), shapes.end(),
    [](const Polygon& polygon) {
    return (polygon.peaks_ % 2 == 0);
  });
}

std::size_t flusova::countOdd(std::vector< Polygon >& shapes) {
  return std::count_if(shapes.begin(), shapes.end(),
    [](const Polygon& polygon) {
    return (polygon.peaks_ % 2 != 0);
  });
}

std::size_t flusova::countNum(int number, std::vector< Polygon >& shapes) {
  return std::count_if(shapes.begin(), shapes.end(),
    [&number](const Polygon& polygon) {
    return (polygon.peaks_ == number);
  });
}
