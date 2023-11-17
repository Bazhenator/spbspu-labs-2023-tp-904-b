#ifndef TYPESTRUCTURES_H
#define TYPESTRUCTURES_H

#include <iosfwd>

namespace lonishin {

  struct UnsignedLongLongIO {
    explicit UnsignedLongLongIO(unsigned long long& ref);
    unsigned long long& ref_;
  };

  struct HexUnsignedLongLongIO {
    explicit HexUnsignedLongLongIO(unsigned long long& ref);
    unsigned long long& ref_;
  };

  struct StringIO {
    explicit StringIO(std::string& ref);
    std::string& ref_;
  };

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, HexUnsignedLongLongIO&& dest);
}

#endif
