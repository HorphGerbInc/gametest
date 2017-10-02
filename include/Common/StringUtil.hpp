
#ifndef _STRINGUTIL_HPP_
#define _STRINGUTIL_HPP_

#include <memory>   // For std::unique_ptr
#include <stdarg.h> // For va_start, etc.
#include <cstring>

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

    namespace jerobins {
  namespace common {
    static std::vector<std::string> Split(std::string str, std::string delims) {
      std::vector<std::string> result;
      std::stringstream ss;
      for_each(str.begin(), str.end(), [&ss, &result, &delims](char c) {
        if (delims.find(c) != delims.npos) {
          std::string candidate = ss.str();
          if (candidate.length() != 0) {
            result.push_back(candidate);
          }
          ss.clear();
        } else {
          ss << c;
        }
      });
      return result;
    }

    static std::string Format(const std::string fmt_str, ...) {
      int final_n, n = ((int)fmt_str.size()) * 2;
      std::unique_ptr<char[]> formatted;
      va_list ap;
      while (1) {
        formatted.reset(
            new char[n]); /* Wrap the plain char array into the unique_ptr */
        std::strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
          n += abs(final_n - n + 1);
        else
          break;
      }
      return std::string(formatted.get());
    }
  }
}

#endif