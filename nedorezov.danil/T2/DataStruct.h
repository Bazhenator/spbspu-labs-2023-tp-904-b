#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <complex>
#include <iosfwd>

#include "iofmtquard.h"
#include "InputStructures.h"

namespace nedorezov {
  struct DataStruct {
    long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  bool operator<(const DataStruct &L, const DataStruct &R);

  std::istream &operator>>(std::istream &in, DataStruct &dest);

  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

}
#endif
