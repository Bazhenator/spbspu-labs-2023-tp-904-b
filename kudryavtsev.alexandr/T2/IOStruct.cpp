#include <iomanip>
#include <iostream>
#include "IOStruct.h"
#include "Structure.h"

UllOctIO::UllOctIO(unsigned long long& ref):
  ref_(ref)
{}

StringIO::StringIO(std::string& ref):
  ref_(ref)
{}

RatLspIO::RatLspIO(std::pair< long long, unsigned long long >& ref):
  ref_(ref)
{}

std::istream& operator>>(std::istream& in, StringIO&& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO('\"');
  std::getline(in, destination.ref_, '\"');
  return in;
}

std::istream& operator>>(std::istream& in, UllOctIO&& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO('0');
  in >> destination.ref_;
  int check = 0;
  check = destination.ref_;
  while (check > 0)
  {
    if (check % 10 >= 8)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    check /= 10;
  }
  return in;
}

std::istream& operator>>(std::istream& in, RatLspIO&& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO('(');
  in >> LabelIO(":N") >> destination.ref_.first;
  in >> LabelIO(":D") >> destination.ref_.second >> DelimeterIO(':');
  in >> DelimeterIO(')');
  return in;
}
