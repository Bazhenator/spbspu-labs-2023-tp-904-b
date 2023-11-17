#include <iostream>
#include "Structure.h"

DelimeterIO::DelimeterIO(char exp):
  exp_(exp)
{}

LabelIO::LabelIO(std::string exp):
  exp_(exp)
{}

std::istream& operator>>(std::istream& in, DelimeterIO&& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != destination.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, LabelIO&& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  if ((in >> data) && (data != destination.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
