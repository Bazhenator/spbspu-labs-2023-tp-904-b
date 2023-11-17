#include "UnitIO.h"

ponomarev::DelimitersIO::DelimitersIO(std::string delimiters):
  delimiters_(delimiters)
{}

ponomarev::LabelIO::LabelIO(std::string label):
  label_(label)
{}

std::istream &ponomarev::operator>>(std::istream &in, DelimitersIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  char c = '0';
  if ((in >> c) && (dest.delimiters_.find(c) == std::string::npos)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  std::string str = "";
  if ((in >> str) && str.compare(dest.label_)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
