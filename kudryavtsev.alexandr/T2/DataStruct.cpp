#include "DataStruct.h"
#include "IOStruct.h"
#include "IOFmtGuard.h"
#include "Structure.h"

std::istream& operator>>(std::istream& in, Data& destination)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Data input;
  in >> DelimeterIO('(') >> DelimeterIO(':');
  for (int i = 0; i < 3; ++i)
  {
    std::string expected;
    in >> expected;
    if (expected == "key1")
    {
      in >> UllOctIO(input.key1);
    }
    else if (expected == "key2")
    {
      in >> RatLspIO(input.key2);
    }
    else if (expected == "key3")
    {
      in >> StringIO(input.key3);
    }
    in >> DelimeterIO(':');
  }
  in >> DelimeterIO(')');
  if (in)
  {
    destination = input;
  return in;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Data& destination)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  Iofmtguard guard(out);
  out << "(:";
  out << "key1 " << "0" << destination.key1 << ":";
  out << "key2 " << "(:N " << destination.key2.first << ":D " << destination.key2.second << ":):";
  out << "key3 " << "\"" << destination.key3 << "\"";
  out << ":)";
  return out;
}

bool operator<(const Data& left, const Data& right)
{
  if (left.key1 == right.key1)
  {
    if (left.key2 == right.key2)
    {
      return left.key3.length() < right.key3.length();
    }
    return left.key2 < right.key2;
  }
  return left.key1 < right.key1;
}
