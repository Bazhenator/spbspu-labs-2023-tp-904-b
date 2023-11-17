#ifndef IOFORMATGUARD_H
#define IOFORMATGUARD_H

#include <ios>

namespace lonishin {
  class IOFormatGuard
  {
  public:
    explicit IOFormatGuard(std::basic_ios< char >& s);
    ~IOFormatGuard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
