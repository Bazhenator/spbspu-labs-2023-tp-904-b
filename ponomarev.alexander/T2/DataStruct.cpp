#include "DataStruct.h"
#include <iostream>
#include <regex>
#include <iomanip>
#include <UnitIO.h>
#include <IOFormatGuard.h>
#include "FieldStructuresIO.h"

bool ponomarev::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}

std::istream &ponomarev::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  DataStruct input;
  in >> DelimitersIO("(") >> DelimitersIO(":");

  static const std::regex regex("key([1-3])");
  std::smatch match;
  std::string key = "";
  for (int i = 0; i < 3; i++) {
    in >> key;
    if (!std::regex_match(key, match, regex)) {
      in.setstate(std::ios::failbit);
    }
    switch (match[1].str()[0] - '0') {
    case 1:
      in >> DoubleIO(input.key1);
      break;
    case 2:
      in >> RealIO(input.key2);
      break;
    case 3:
      in >> StringIO(input.key3);
      break;
    default:
      break;
    }
    in >> DelimitersIO(":");
  }
  in >> DelimitersIO(")");

  if (in) {
    dest = input;
  }
  return in;
}

std::ostream &ponomarev::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }

  IOFormatGuard fmtguard(out);

  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d:";
  out << "key2 " << "(:N " << src.key2.first << ":D " << src.key2.second << ":):";
  out << "key3 " << "\"" << src.key3 << "\"";
  out << ":)";

  return out;
}
