
#ifndef _ARGUMENTCHECK_HPP_
#define _ARGUMENTCHECK_HPP_

#include <sstream>

namespace jerobins {
  namespace common {

    /**
     *  \class ArgumentCheck
     *  \ingroup Common
     *
     *  @brief This class is used for argument validation.
     *
     *  \author   $Author: JAR$
     *  \version  $Revision 1.5$
     *  \date     $Date: 2/24/2018$
     * 
     * @param T   Type of object we are validating.
     */

    template <typename T> class ArgumentCheck {

    public:
      /**
       * @brief Validates the assertion throws an exception on failure.
       *
       *
       * @param check   The check that was performed.
       * @param msg     The message to display on failure.
       * @param object  The object we were validating.
       */
      ArgumentCheck(bool check, std::string msg, T object) {
        if (!check) {
          std::stringstream ss;
          ss << msg << ":" << object;
          throw std::runtime_error(ss.str());
        }
      }

      /**
       * @brief Checks the assertion and throwns an exception with a predefined
       * message.
       *
       * @param check The assertion to validate.
       * @param msg   The message to throw on validation failure.
       */
      ArgumentCheck(bool check, std::string msg) {
        if (!check) {
          throw std::runtime_error(msg);
        }
      }

      /**
       * @brief Validates a pointer is not nul and throws an exception on
       * failure.
       *
       * @param name      The name of the pointer object.
       * @param argument  The pointer object.
       */
      static void IsNotNull(const std::string name, const T *argument) {
        if (argument == NULL || argument == nullptr) {
          throw new std::runtime_error(name + " is null");
        }
      }
    };
  } // namespace common
} // namespace jerobins

#endif