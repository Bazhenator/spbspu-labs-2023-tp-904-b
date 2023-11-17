#ifndef MANAGE_DATA_H
#define MANAGE_DATA_H

#include <iosfwd>
#include <complex>
#include <string>

namespace flusova {

  struct DataStruct {
    double key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::string convertToSCI(const double& ref);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool operator<(DataStruct& left, DataStruct& right);
}

#endif
