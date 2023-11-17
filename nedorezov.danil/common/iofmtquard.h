#ifndef IOFMTQUARD_H
#define IOFMTQUARD_H

#include <iostream>

namespace nedorezov {
  class iofmtguard {
  public:
    explicit iofmtguard(std::basic_ios< char > &s);

    ~iofmtguard();

  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
