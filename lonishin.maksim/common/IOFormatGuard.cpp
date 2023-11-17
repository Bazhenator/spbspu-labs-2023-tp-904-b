#include "IOFormatGuard.h"

lonishin::IOFormatGuard::IOFormatGuard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  fmt_(s.flags())
{}

lonishin::IOFormatGuard::~IOFormatGuard() {
  s_.fill(fill_);
  s_.flags(fmt_);
}
