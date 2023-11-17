#include "IOFmtGuard.h"

Iofmtguard::Iofmtguard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  fmt_(s.flags())
{}

Iofmtguard::~Iofmtguard()
{
  s_.fill(fill_);
  s_.flags(fmt_);
}
