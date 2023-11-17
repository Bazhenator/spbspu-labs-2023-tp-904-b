#include "InputStructures.h"

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::DelimeterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp_)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::LongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> dest.ref_ >> DelimeterIO{'l'} >> DelimeterIO{'l'};
  return in;
}

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::ComplexIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  double real;
  double imag;
  in >> nedorezov::DelimeterIO{'#'} >> nedorezov::DelimeterIO{'c'};
  in >> nedorezov::DelimeterIO{'('} >> real >> imag;
  in >> nedorezov::DelimeterIO{')'};
  dest.ref_.real(real);
  dest.ref_.imag(imag);
  return in;
}

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> nedorezov::DelimeterIO{'"'}, dest.ref_, '"');
}
