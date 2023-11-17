#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <iosfwd>

struct DelimeterIO
{
  explicit DelimeterIO(char exp);
  char exp_;
};

struct LabelIO
{
  explicit LabelIO(std::string exp);
  std::string exp_;
};

std::istream& operator>>(std::istream& in, DelimeterIO&& destination);
std::istream& operator>>(std::istream& in, LabelIO&& destination);
#endif
