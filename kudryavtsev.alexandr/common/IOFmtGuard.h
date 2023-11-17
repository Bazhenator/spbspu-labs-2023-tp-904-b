#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H

#include <iostream>

class Iofmtguard
{
public:
  explicit Iofmtguard(std::basic_ios< char >& s);
  ~Iofmtguard();
private:
  std::basic_ios< char >& s_;
  char fill_;
  std::basic_ios< char >::fmtflags fmt_;
};
#endif
