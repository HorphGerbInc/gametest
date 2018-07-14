
#include <Common/CommandLineArguments.hpp>

#include <Common/CommandLineArgumentException.hpp>
#include <Common/EndOfInputException.hpp>
#include <Common/Util.hpp>

#include <algorithm>

namespace jerobins {
  namespace common {
    CommandLineArguments::CommandLineArguments() { /* Empty */
    }

    // Parameter
    void CommandLineArguments::AddParameter(const std::string &parameter) {
      if (!jerobins::common::Contains(parameters, parameter)) {
        parameters.push_back(parameter);
      }
    }

    void CommandLineArguments::AddParameter(const std::string &&parameter) {
      AddParameter(parameter);
    }

    bool
    CommandLineArguments::ParameterSet(const std::string &parameter) const {
      return jerobins::common::Contains(mappings, parameter);
    }

    bool
    CommandLineArguments::ParameterSet(const std::string &&parameter) const {
      return jerobins::common::Contains(mappings, parameter);
    }

    std::string
    CommandLineArguments::ParameterValue(const std::string &parameter) const {
      auto iter = mappings.find(parameter);
      return iter->second;
    }

    std::string
    CommandLineArguments::ParameterValue(const std::string &&parameter) const {
      return ParameterValue(parameter);
    }

    // Flags
    void CommandLineArguments::AddFlag(const std::string &flag) {
      if (!jerobins::common::Contains(flags, flag)) {
        flags.push_back(flag);
      }
    }

    void CommandLineArguments::AddFlag(const std::string &&flag) {
      AddFlag(flag);
    }

    bool CommandLineArguments::FlagSet(const std::string &flag) const {
      return jerobins::common::Contains(flagsSeen, flag);
    }

    bool CommandLineArguments::FlagSet(const std::string &&flag) const {
      return jerobins::common::Contains(flagsSeen, flag);
    }

    // Parse
    void CommandLineArguments::Parse(int argc, char *argv[]) {
      // Skip the name of the program
      ++argv;
      --argc;
      int pos = 0;
      while (pos < argc) {
        auto token = std::string(argv[pos]);

        if (token[0] == '-') {
          token = token.substr(1);
        }

        auto posOfEqual = std::find(token.begin(), token.end(), '=');

        if (posOfEqual != token.end()) {
          auto key = std::string(token.begin(), posOfEqual);

          if (!jerobins::common::Contains(parameters, key)) {
            throw jerobins::common::CommandLineArgumentException(key, token);
          }

          auto value = std::string(posOfEqual + 1, token.end());

          if (value.size() == 0) {
            throw std::runtime_error("key has no value: " + key);
          }

          mappings.insert(std::pair<std::string, std::string>(key, value));
          ++pos;
        } else if (jerobins::common::Contains(parameters, token)) {
          auto key = token;
          ++pos;

          if (pos == argc) {
            throw jerobins::common::CommandLineEndOfInputException(key);
          }

          auto value = argv[pos];
          mappings.insert(std::pair<std::string, std::string>(key, value));
          ++pos;
        } else if (jerobins::common::Contains(flags, token)) {
          flagsSeen.push_back(token);
          ++pos;
        } else {
          throw jerobins::common::CommandLineEndOfInputException(token);
        }
      }
    }
  }
}
