
#ifndef _STRINGUTIL_HPP_
#define _STRINGUTIL_HPP_

#include <stdarg.h> // For va_start, etc.
#include <string>
#include <vector>

namespace jerobins {
  namespace common {
    /**
     * @brief String utilities.
     *
     */
    class StringUtil {
    public:
      /**
       * @brief Given a list of delimiters split a string.
       *
       * @param str         The string to split.
       * @param delims      The delimiters.
       * @param keepEmpty   Denotes that we should keep or remove empty strings.
       * @return std::vector<std::string> The list of split strings.
       */
      static std::vector<std::string> Split(std::string str, std::string delims,
                                            bool keepEmpty = false);

      /**
       * @brief Fill in a format string with values.
       *
       * @param fmt_str       The format string.
       * @param ...           The parameters to the format string.
       * @return std::string  The string with the parameters inserted.
       */
      static std::string Format(const std::string fmt_str, ...);
    };
  } // namespace common
} // namespace jerobins
#endif