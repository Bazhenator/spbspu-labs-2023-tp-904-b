#include "Separators.h"
#include <string>
#include <iomanip>
#include "iofmtguard.h"

std::istream& flusova::operator>>(std::istream& in, flusova::Delimetr&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
