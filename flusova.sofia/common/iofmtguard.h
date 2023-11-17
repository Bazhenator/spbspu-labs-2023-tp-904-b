#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H

#include <ios>

namespace flusova {
  class iofmtguard {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
