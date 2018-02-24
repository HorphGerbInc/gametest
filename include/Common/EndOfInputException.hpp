
#ifndef _UNKNOWNARGUMENTEXCEPTION_HPP_
#define _UNKNOWNARGUMENTEXCEPTION_HPP_

#include <sstream>
#include <stdexcept>
#include <string>

namespace jerobins {
  namespace common {

    /**
     * @brief Represents an exception where we have reached to end of input
     * during parsing the command line arguments.
     *
     */
    class CommandLineEndOfInputException : public std::runtime_error {

    private:
      std::string exceptionMessaage;

    public:
      /**
       * @brief Reached the end of input while parsing this parameter on the
       * command line.
       *
       * @param parameter
       */
      CommandLineEndOfInputException(std::string parameter)
          : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "Reached end of input while reading parameter: ";
        stringStream << parameter;
        exceptionMessaage = stringStream.str();
      }
      /**
       * @brief Return the formatted exception.
       *
       * @return const char*  C string containing exception message.
       */
      const char *what() const throw() { return exceptionMessaage.c_str(); }
    };
  } // namespace common
} // namespace jerobins
#endif