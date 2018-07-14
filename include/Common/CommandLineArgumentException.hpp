
#ifndef _COMMANDLINEARGUMENTEXCEPTION_HPP_
#define _COMMANDLINEARGUMENTEXCEPTION_HPP_

#include <sstream>
#include <stdexcept>
#include <string>

namespace jerobins {
  namespace common {
    /**
     * @brief Represents an invalid command line argument.
     *
     */
    class CommandLineArgumentException : public std::runtime_error {

    private:
      std::string exceptionMessaage;

    public:
      /**
       * @brief Displays an error message along with the parameter.
       *
       * @param msg         Message to display in the exception.
       * @param parameter   Parameter displayed in the exception.
       */
      CommandLineArgumentException(std::string msg, std::string parameter)
          : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "[parameter=" << parameter << "]: " << msg;
        exceptionMessaage = stringStream.str();
      }

      /**
       * @brief Displays an error message along with the token and parameter.
       *
       * @param msg         Message to display in the exception.
       * @param parameter   Parameter displayed in the exception.
       * @param token       Token displayed in the exception.
       */
      CommandLineArgumentException(std::string msg, std::string parameter,
                                   std::string token)
          : std::runtime_error("") {
        std::ostringstream stringStream;
        stringStream << "[parameter=" << parameter << ","
                     << "token=" << token << "]: " << msg;
        exceptionMessaage = stringStream.str();
      }

      /**
       * @brief Returns a C string of the exception message.
       *
       * @return const char*  String representation of the exception.
       */
      const char *what() const throw() { return exceptionMessaage.c_str(); }
    };
  } // namespace common
} // namespace jerobins
#endif