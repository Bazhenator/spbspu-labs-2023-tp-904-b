#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

struct Data
{
  unsigned long long key1 = 0;
  std::pair< long long, unsigned long long > key2;
  std::string key3;
};

std::istream& operator>>(std::istream& in, Data& destination);
std::ostream& operator<<(std::ostream& out, const Data& destination);
bool operator<(const Data& left, const Data& right);

#endif
