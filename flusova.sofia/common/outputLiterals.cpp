#include "outputLiterals.h"
#include <limits>
#include "iofmtguard.h"

void flusova::printEmpty(std::ostream& out)
{
  out << "<EMPTY>" << '\n';
}

void flusova::printInvalidCmd(std::ostream& out, std::istream& in)
{
  flusova::iofmtguard fmtguard(out);
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  out << "<INVALID COMMAND>" << '\n';
}
