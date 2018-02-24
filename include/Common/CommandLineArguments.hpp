
#ifndef _COMMANDLINEARGUMENTS_HPP_
#define _COMMANDLINEARGUMENTS_HPP_

#include <map>
#include <string>
#include <vector>

namespace jerobins {
  namespace common {

    /**
     * @brief     Represents command line arguments.
     *
     * @detailed  Represents command line arguments of the form:
     *  - key value
     *  - key=value
     *  - -key=value
     *  - -flag
     *  - flag
     *
     * Note that this means you cannot have a flag and key with the
     * same value.
     */
    class CommandLineArguments {

    private:
      // List of allowed parameters
      std::vector<std::string> parameters;

      // List of allowed flags
      std::vector<std::string> flags;

      // Parameter and their found values.
      std::map<std::string, std::string> mappings;

      // List of seen flags
      std::vector<std::string> flagsSeen;

    public:
      CommandLineArguments();

      /**
       * @brief Add a new allowed parameter.
       *
       * @param parameter The name of the parameter.
       */
      void AddParameter(const std::string &parameter);

      /**
       * @brief Add a new allowed parameter.
       *
       * @param parameter The name of the parameter.
       */
      void AddParameter(const std::string &&parameter);

      /**
       * @brief           Checks if a parameter has been set.
       *
       * @param parameter The name of the parameter.
       * @return true     The parameter has a value.
       * @return false    The parameter has no value.
       */
      bool ParameterSet(const std::string &parameter) const;

      /**
       * @brief           Checks if a parameter has been set.
       *
       * @param parameter The name of the parameter.
       * @return true     The parameter has a value.
       * @return false    The parameter has no value.
       */
      bool ParameterSet(const std::string &&parameter) const;

      /**
       * @brief               Returns the value of the parameter.
       *
       * @detailed            Returns the value of the parameter if it has been
       * set.  If the value has not been set the behviour is undefined.
       *
       * @param parameter     The name of the parameter.
       * @return std::string  The value of the parameter.
       */
      std::string ParameterValue(const std::string &parameter) const;

      /**
       * @brief               Returns the value of the parameter.
       *
       * @detailed            Returns the value of the parameter if it has been
       * set.  If the value has not been set the behviour is undefined.
       *
       * @param parameter     The name of the parameter.
       * @return std::string  The value of the parameter.
       */
      std::string ParameterValue(const std::string &&parameter) const;

      /**
       * @brief       Add new flag command line argument.
       *
       * @param flag  The name of the flag.
       */
      void AddFlag(const std::string &flag);

      /**
       * @brief       Add new flag command line argument.
       *
       * @param flag  The name of the flag.
       */
      void AddFlag(const std::string &&flag);

      /**
       * @brief         Check if the flag has been set or not.
       *
       * @param flag    The name of the flag.
       * @return true   The flag has been set.
       * @return false  The flag has not been set.
       */
      bool FlagSet(const std::string &flag) const;

      /**
       * @brief         Check if the flag has been set or not.
       *
       * @param flag    The name of the flag.
       * @return true   The flag has been set.
       * @return false  The flag has not been set.
       */
      bool FlagSet(const std::string &&flag) const;

      void Parse(int argc, char *argv[]);
    };
  } // namespace common
} // namespace jerobins

#endif