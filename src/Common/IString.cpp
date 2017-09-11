
#include <Common/IString.hpp>

std::ostream &operator<<(std::ostream &os,
                         const jerobins::common::IString &str) {
  return os << str.ToString();
}

std::ostream &operator<<(std::ostream &os,
                         const jerobins::common::IString &&str) {
  return os << str;
}