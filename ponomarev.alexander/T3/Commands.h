#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>
#include <cstddef>
#include <iosfwd>
#include <functional>
#include <iterator>
#include <utility>
#include <map>
#include "BaseShapes.h"
#include "PolygonOperations.h"

namespace ponomarev {
  class Commands {
    public:
      Commands(std::vector< Polygon > shapes, std::istream &is, std::ostream &os);

      void computeArea();
      void findMax();
      void findMin();
      void countShapes();
      void countRectangles();
      void isInFrame();
    private:
      static const std::map< std::string, std::function< bool(const Polygon &) > > filters_;
      static const std::map< std::string, std::function< bool(const Polygon &, const Polygon &) > > comparators_;
      std::vector< Polygon > shapes_;
      std::istream &is_;
      std::ostream &os_;
  };

  void printInvalid(std::ostream &os);
}

#endif
