
#ifndef _UNKNOWNARGUMENTEXCEPTION_HPP_
#define _UNKNOWNARGUMENTEXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace jerobins {
  namespace common {

    class EndOfInputException : public std::runtime_error {

    private:
      std::string exceptionMessaage;

    public:
      // Cannot match token with anything
      EndOfInputException(std::string parameter) : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "Reached end of input while reading parameter: ";
        stringStream << parameter;
        exceptionMessaage = stringStream.str();
      }

      const char *what() const throw() { return exceptionMessaage.c_str(); }
    };
  }
}
#endif