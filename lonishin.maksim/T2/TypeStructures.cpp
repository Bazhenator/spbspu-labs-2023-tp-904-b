#include "TypeStructures.h"
#include <iostream>
#include <IOFormatGuard.h>
#include <HelperStructsIO.h>


lonishin::UnsignedLongLongIO::UnsignedLongLongIO(unsigned long long& ref):
  ref_(ref)
{}

lonishin::StringIO::StringIO(std::string& ref):
  ref_(ref)
{}

lonishin::HexUnsignedLongLongIO::HexUnsignedLongLongIO(unsigned long long& ref):
  ref_(ref)
{}

std::istream& lonishin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> lonishin::DelimeterIO{'"'}, dest.ref_, '"');
}

std::istream& lonishin::operator>>(std::istream& in, UnsignedLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref_ >> DelimeterIO{'u'} >> DelimeterIO{'l'} >> DelimeterIO{'l'};
}

std::istream& lonishin::operator>>(std::istream& in, HexUnsignedLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  IOFormatGuard format(in);
  return in >> DelimeterIO{'0'} >> DelimeterIO{'x'} >> std::hex >> dest.ref_;
}
