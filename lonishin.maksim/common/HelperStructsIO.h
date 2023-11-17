#ifndef HELPERSTRUCTSIO_H
#define HELPERSTRUCTSIO_H

#include <iosfwd>
#include <string>

namespace lonishin {

  struct DelimeterIO {
    explicit DelimeterIO(char exp);
    char exp_;
  };

  struct LabelIO {
    explicit LabelIO(std::string exp);
    std::string exp_;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
