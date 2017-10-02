
#ifndef _STRINGUTIL_HPP_
#define _STRINGUTIL_HPP_

#include <stdarg.h> // For va_start, etc.
#include <string>
#include <vector>

namespace jerobins {
  namespace common {
    class StringUtil {
    public:
      // Split a string using delimeters
      static std::vector<std::string> Split(std::string str,
                                            std::string delims);

      // format a string
      static std::string Format(const std::string fmt_str, ...);
    };
  }
}
#endif