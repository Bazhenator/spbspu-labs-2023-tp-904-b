#include "typeSystem.h"
#include <string>
#include <iomanip>
#include <cmath>
#include <complex>
#include "iofmtguard.h"
#include "Separators.h"

std::istream& flusova::operator>>(std::istream& in, flusova::DoubleSCI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::scientific >> dest.ref_;
}

std::istream& flusova::operator>>(std::istream& in, flusova::ComplexDBL&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double real;
  double imag;
  in >> flusova::Delimetr{ '#' } >> flusova::Delimetr{ 'c' };
  in >> flusova::Delimetr{ '(' } >> real >> imag >> flusova::Delimetr{ ')' };
  dest.ref_.real(real);
  dest.ref_.imag(imag);
  return in;
}

std::istream& flusova::operator>>(std::istream& in, flusova::String&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> flusova::Delimetr{ '"' }, dest.ref_, '"');
}

