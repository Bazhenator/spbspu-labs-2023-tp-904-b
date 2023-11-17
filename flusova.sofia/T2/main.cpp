#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "manageData.h"

int main()
{
  std::vector< flusova::DataStruct > data;
  while (!std::cin.eof()) {
    std::cin.clear();
    std::copy(
      std::istream_iterator< flusova::DataStruct >(std::cin),
      std::istream_iterator< flusova::DataStruct >(),
      std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< flusova::DataStruct >(std::cout, "\n")
  );
  return 0;
}
