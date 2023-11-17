#ifndef IO_STRUCT_H
#define IO_STRUCT_H

#include <string>
#include <iosfwd>

struct StringIO
{
  explicit StringIO(std::string& ref);
  std::string& ref_;
};

struct UllOctIO
{
  explicit UllOctIO(unsigned long long& ref);
  unsigned long long& ref_;
};

struct RatLspIO
{
  explicit RatLspIO(std::pair< long long, unsigned long long >& ref);
  std::pair< long long, unsigned long long >& ref_;
};

std::istream& operator>>(std::istream& in, StringIO&& destination);
std::istream& operator>>(std::istream& in, UllOctIO&& destination);
std::istream& operator>>(std::istream& in, RatLspIO&& destination);
#endif
