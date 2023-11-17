#include "DataStruct.h"

#include <iomanip>

bool nedorezov::operator<(const nedorezov::DataStruct &L, const nedorezov::DataStruct &R)
{
  if (L.key1 == R.key1) {
    if (L.key2 == R.key2) {
      return L.key3 < R.key3;
    }
    return abs(L.key2) < abs(R.key2);
  }
  return L.key1 < R.key1;
}

std::istream &nedorezov::operator>>(std::istream &in, nedorezov::DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  nedorezov::DataStruct input;
  {
    using sep = nedorezov::DelimeterIO;
    in >> sep{'('};
    in >> sep{':'};
    std::string key;
    for (int i = 0; i < 3; ++i) {
      in >> key;
      if (key == "key1") {
        using ll = nedorezov::LongLongIO;
        in >> ll{input.key1};
      } else if (key == "key2") {
        using cmpl = nedorezov::ComplexIO;
        in >> cmpl{input.key2};
      } else if (key == "key3") {
        using str = nedorezov::StringIO;
        in >> str{input.key3};
      } else {
        in.setstate(std::ios::failbit);
      }
      in >> sep{':'};
    }
    in >> sep{')'};
    if (in) {
      dest = input;
    }
  }
  return in;
}

std::ostream &nedorezov::operator<<(std::ostream &out, const nedorezov::DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  nedorezov::iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << std::fixed << std::setprecision(1) <<  src.key1 << "ll";
  out << ":key2 " << "#c(" << src.key2.real() << " " << src.key2.imag() << ")";
  out << ":key3 \"" << src.key3 << '\"';
  out << ":)";
  return out;
}
