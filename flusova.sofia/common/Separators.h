#ifndef SEPARATORS_H
#define SEPARATORS_H

#include <string>
#include <iosfwd>

namespace flusova {
  struct Delimetr {
    char exp_;
  };
  std::istream& operator>>(std::istream& in, Delimetr&& dest);
}

#endif
