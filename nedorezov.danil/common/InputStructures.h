#ifndef INPUT_STRUCTURES_H
#define INPUT_STRUCTURES_H

#include <complex>
#include <iosfwd>

namespace nedorezov {
  struct DelimeterIO {
    char exp_;
  };

  struct LongLongIO {
    long long &ref_;
  };

  struct ComplexIO {
    std::complex< double > &ref_;
  };

  struct StringIO {
    std::string &ref_;
  };

  std::istream &operator>>(std::istream &in, DelimeterIO &&dest);

  std::istream &operator>>(std::istream &in, LongLongIO &&dest);

  std::istream &operator>>(std::istream &in, ComplexIO &&dest);

  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
