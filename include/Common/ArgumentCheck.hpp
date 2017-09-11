
#ifndef _ARGUMENTCHECK_HPP_
#define _ARGUMENTCHECK_HPP_

#include <sstream>

namespace jerobins {
  namespace common {

    template <typename T> class ArgumentCheck {

    public:
      ArgumentCheck(bool check, std::string msg, T object) {
        if (!check) {
          std::stringstream ss;
          ss << msg << ":" << object;
          throw std::runtime_error(ss.str());
        }
      }

      ArgumentCheck(bool check, std::string msg) {
        if (!check) {
          throw std::runtime_error(msg);
        }
      }
    };
  }
}

#endif