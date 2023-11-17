#include "DataStruct.h"
#include <iostream>
#include <IOFormatGuard.h>
#include <HelperStructsIO.h>
#include "TypeStructures.h"

std::istream& lonishin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
   {
    using sep = DelimeterIO;
    in >> sep{'('};
    in >> sep{':'};
    for (int i = 0; i < 3; ++i) {
      using hex = HexUnsignedLongLongIO;
      using ull = UnsignedLongLongIO;
      using str = StringIO;
      std::string key = "";
      in >> key;
      if (key == "key1") {
        in >> ull{input.key1_};
      } else if (key == "key2") {
        in >> hex{input.key2_};
      } else if (key == "key3") {
        in >> str{input.key3_};
      }
      in >> sep{':'};
    }
    in >> sep{')'};
  }
  if (in) {
    dest = input;
  }
  return in;
}

std::ostream& lonishin::operator<<(std::ostream& out, const lonishin::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  IOFormatGuard format(out);
  out << "(";
  out << ":key1 " << src.key1_ << "ull";
  out << ":key2 0x" << std::hex << std::uppercase << src.key2_;
  out << ":key3 \"" << src.key3_ << '"';
  out << ":)";
  return out;
}

bool lonishin::operator<(const lonishin::DataStruct& first, const lonishin::DataStruct& second)
{
  if (first.key1_ != second.key1_) {
    return first.key1_ < second.key1_;
  }
  if (first.key2_ != second.key2_) {
    return first.key2_ < second.key2_;
  }
  return first.key3_ < second.key3_;
}
