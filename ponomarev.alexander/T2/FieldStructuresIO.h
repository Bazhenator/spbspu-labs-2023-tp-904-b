#ifndef FIELD_STRUCTURES_IO_H
#define FIELD_STRUCTURES_IO_H

#include <utility>
#include <string>
#include <iostream>

namespace ponomarev {
  struct DoubleIO {
    public:
      explicit DoubleIO(double &ref);

      friend std::istream &operator>>(std::istream &in, DoubleIO &&dest);
    private:
      double &ref_;
  };

  struct RealIO {
    public:
      explicit RealIO(std::pair< long long, unsigned long long > &real);

      friend std::istream &operator>>(std::istream &in, RealIO &&dest);
    private:
      std::pair< long long, unsigned long long > &ref_;
  };

  struct StringIO {
    public:
      explicit StringIO(std::string &ref);

      friend std::istream &operator>>(std::istream &in, StringIO &&dest);
    private:
      std::string &ref_;
  };

  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, RealIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
