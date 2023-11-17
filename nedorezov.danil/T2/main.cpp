#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "DataStruct.h"

int main()
{
  std::vector< nedorezov::DataStruct > dataStructs;
  while (!std::cin.eof()) {
    std::cin.clear();
    std::copy(
            std::istream_iterator< nedorezov::DataStruct >(std::cin),
            std::istream_iterator< nedorezov::DataStruct >(),
            std::back_inserter(dataStructs)
    );
  }
  std::sort(dataStructs.begin(), dataStructs.end());
  std::copy(
          std::begin(dataStructs),
          std::end(dataStructs),
          std::ostream_iterator< nedorezov::DataStruct >(std::cout, "\n")
  );
  return 0;
}
