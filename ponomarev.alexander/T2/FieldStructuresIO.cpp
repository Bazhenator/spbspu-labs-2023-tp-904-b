#include "FieldStructuresIO.h"
#include <UnitIO.h>

ponomarev::DoubleIO::DoubleIO(double &ref):
  ref_(ref)
{}

ponomarev::RealIO::RealIO(std::pair<long long, unsigned long long> &real):
  ref_(real)
{}

ponomarev::StringIO::StringIO(std::string &ref):
  ref_(ref)
{}

std::istream &ponomarev::operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  return in >> dest.ref_ >> DelimitersIO("dD");
}

std::istream &ponomarev::operator>>(std::istream &in, RealIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  in >> DelimitersIO("(") >> LabelIO(":N") >> dest.ref_.first;
  in >> LabelIO(":D") >> dest.ref_.second >> DelimitersIO(":") >> DelimitersIO(")");
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  in >> DelimitersIO("\"");
  std::getline(in, dest.ref_, '\"');
  return in;
}
