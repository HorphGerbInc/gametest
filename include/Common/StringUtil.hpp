
#ifndef _STRINGUTIL_HPP_
#define _STRINGUTIL_HPP_

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace jerobins {
  namespace common {
    static std::vector<std::string> Split(std::string str, std::string delims) {
      std::vector<std::string> result;
      std::stringstream ss;
      for_each(str.begin(), str.end(), [&ss,&result,&delims](char c) {
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
  }
}

#endif