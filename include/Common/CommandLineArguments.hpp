
#ifndef _COMMANDLINEARGUMENTS_HPP_
#define _COMMANDLINEARGUMENTS_HPP_

#include <map>
#include <string>
#include <vector>

namespace jerobins {
  namespace common {
    /*
    *  Command line argument helper class.  Can handle arguments of the
    * form:
    *      key value
    *      key=value
    *      -key=value
    *      -flag
    *      flag
    *
    *     Note that this means you cannot have a flag and key with the
    *     same value.
    *
    */
    class CommandLineArguments {
    private:
      // Parameters to look for
      std::vector<std::string> parameters;
      // Flags to look for
      std::vector<std::string> flags;

      // Parameters and their values
      std::map<std::string, std::string> mappings;
      // Flags seen
      std::vector<std::string> flagsSeen;

    public:
      CommandLineArguments();

      void AddParameter(const std::string &&parameter);
      bool ParameterSet(const std::string && parameter) const;
      std::string ParameterValue(const std::string && parameter) const;
      
      void AddFlag(const std::string &&flag);
      bool FlagSet(const std::string && flag) const;

      void Parse(int argc, char *argv[]);
    };
  }
}

#endif