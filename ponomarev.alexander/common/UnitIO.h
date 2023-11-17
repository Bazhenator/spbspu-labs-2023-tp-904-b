#ifndef UNIT_IO_H
#define UNIT_IO_H

#include <string>
#include <iostream>

namespace ponomarev {
  struct DelimitersIO {
    public:
      explicit DelimitersIO(std::string delimiters);

      friend std::istream &operator>>(std::istream &in, DelimitersIO &&dest);
    private:
      std::string delimiters_;
  };

  struct LabelIO {
    public:
      explicit LabelIO(std::string label);

      friend std::istream &operator>>(std::istream &in, LabelIO &&dest);
    private:
      std::string label_;
  };

  std::istream &operator>>(std::istream &in, DelimitersIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
}

#endif
