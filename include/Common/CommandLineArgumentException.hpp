
#ifndef _COMMANDLINEARGUMENTEXCEPTION_HPP_
#define _COMMANDLINEARGUMENTEXCEPTION_HPP_

#include <sstream>
#include <stdexcept>
#include <string>

namespace jerobins {
  namespace common {

    class CommandLineArgumentException : public std::runtime_error {

    private:
      std::string exceptionMessaage;

    public:
      // Cannot match token with anything
      CommandLineArgumentException(std::string parameter)
          : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "Cannot match with expected parameters and flags: ";
        stringStream << parameter;
        exceptionMessaage = stringStream.str();
      }

      CommandLineArgumentException(std::string parameter, std::string token)
          : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "Cannot match with expected parameters and flags: ";
        stringStream << parameter;
        stringStream << " from ";
        stringStream << token;
        exceptionMessaage = stringStream.str();
      }

      const char *what() const throw() { return exceptionMessaage.c_str(); }
    };
  }
}
#endif