
#ifndef _ISTRING_HPP_
#define _ISTRING_HPP_

#include <ostream>
#include <string>

namespace jerobins {
  namespace common {
      ///
      ///   Base class for all object that want to support ToString.
      ///
    class IString {
    public:
      virtual std::string ToString() const = 0;
    };
  }
}

// Stream functions
std::ostream& operator<<(std::ostream &os, const jerobins::common::IString &str);
std::ostream& operator<<(std::ostream &os, const jerobins::common::IString &&str);

#endif