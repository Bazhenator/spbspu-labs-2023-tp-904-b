#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <utility>
#include <string>
#include <iosfwd>

namespace ponomarev {
  struct DataStruct {
    public:
      friend bool operator<(const DataStruct &lhs, const DataStruct &rhs);
      friend std::istream &operator>>(std::istream &in, DataStruct &dest);
      friend std::ostream &operator<<(std::ostream &out, const DataStruct &src);
    private:
      double key1;
      std::pair< long long, unsigned long long > key2;
      std::string key3;
  };

  bool operator<(const DataStruct &lhs, const DataStruct &rhs);

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}

#endif
