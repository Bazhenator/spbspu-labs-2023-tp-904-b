#ifndef TYPE_SYSTEM_H
#define TYPE_SYSTEM_H

#include <iosfwd>
#include <string>
#include <complex>

namespace flusova {
  struct DoubleSCI {
    double& ref_;
  };

  struct ComplexDBL {
    std::complex< double >& ref_;
  };

  struct String {
    std::string& ref_;
  };

  std::istream& operator>>(std::istream& in, DoubleSCI&& dest);
  std::istream& operator>>(std::istream& in, ComplexDBL&& dest);
  std::istream& operator>>(std::istream& in, String&& dest);

}

#endif
