
#ifndef _ISTRING_HPP_
#define _ISTRING_HPP_

#include <ostream>
#include <string>

namespace jerobins {
  namespace common {
    /**
     * @brief The ToString interface class.
     *
     * @detailed  All classes who inherit from this class must support ToString.
     */
    class IString {
    public:
      /**
       * @brief Return a string representation of the object.
       *
       * @return std::string  The string representation of the object.
       */
      virtual std::string ToString() const = 0;
    };
  } // namespace common
} // namespace jerobins

// Stream functions

/**
 * @brief Default output stream operation for all classes who support ToString.
 *
 * @param os              The output stream to write to.
 * @param obj             The object which supports ToString.
 * @return std::ostream&  Returns the output stream passed in.
 */
std::ostream &operator<<(std::ostream &os,
                         const jerobins::common::IString &obj);

/**
 * @brief Default output stream operation for all classes who support ToString.
 *
 * @param os              The output stream to write to.
 * @param obj             The object which supports ToString.
 * @return std::ostream&  Returns the output stream passed in.
 */
std::ostream &operator<<(std::ostream &os,
                         const jerobins::common::IString &&obj);

#endif