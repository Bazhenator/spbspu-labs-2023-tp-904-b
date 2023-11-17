#include "manageData.h"
#include "typeSystem.h"
#include "iofmtguard.h"
#include "Separators.h"

#include <iomanip>

std::string flusova::convertToSCI(const double& ref) {
  std::ostringstream stream;
  stream << std::scientific << std::setprecision(1) << ref;
  std::string result = stream.str();
  for (std::size_t i = result.find("-"); i <= result.size(); i++) {
    if (result[i] == '0') {
      result.erase(result.begin() + i);
    }
  }
  for (std::size_t i = result.find("+"); i <= result.size(); i++) {
    if (result[i] == '0') {
      result.erase(result.begin() + i);
    }
  }
  return result;
}

std::istream& flusova::operator>>(std::istream& in, flusova::DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  flusova::DataStruct input;
  {
    using sep = flusova::Delimetr;
    in >> sep{ '(' } >> sep{ ':' };
    std::size_t cnt = 0;
    std::string key;
    do {
      in >> key;
      if (key == "key1") {
        in >> flusova::DoubleSCI{input.key1};
      } else if (key == "key2") {
        in >> flusova::ComplexDBL{input.key2};
      } else if (key == "key3") {
        in >> flusova::String{input.key3};
      } else {
        in.setstate(std::ios::failbit);
      }
      in >> sep{ ':' };
      cnt++;
    } while (cnt < 3);
    in >> sep{')'};
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& flusova::operator<<(std::ostream& out, const flusova::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  flusova::iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << flusova::convertToSCI(src.key1);
  out << ":key2 " << std::fixed << std::setprecision(1) << "#c(" << src.key2.real() << " " << src.key2.imag() << ")";
  out << ":key3 \"" << src.key3 << '\"';
  out << ":)";
  return out;
}

bool flusova::operator<(flusova::DataStruct& lhs, flusova::DataStruct& rhs) {
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  } else {
    if (lhs.key2 != rhs.key2) {
      return abs(lhs.key2) < abs(rhs.key2);
    } else {
      return lhs.key3.size() < rhs.key3.size();
    }
  }
}
