
#include <Common/Configuration.hpp>

namespace jerobins {
  namespace common {

    const jerobins::common::Version Configuration::Version(0, 1, 0);

    Configuration::Configuration() { /* Empty */
    }

    // Create a configuration object from another
    Configuration::Configuration(const Configuration &other)
        : mappings(other.mappings) {
      /* Empty */
    }

    Configuration &Configuration::operator=(const Configuration &other) {
      std::map<std::string, char *> tmp(other.mappings);
      this->mappings = tmp;
      return *this;
    }

    // Remove the configuration value
    void Configuration::Delete(std::string key) {
      auto iter = mappings.find(key);
      if (iter != mappings.end()) {
        delete iter->second;
        mappings.erase(iter);
      }
    }

    static Configuration Deserialize(std::istream &input) {
      Configuration config;
      std::string line;
      while (std::getline(input, line)) {
        std::vector<std::string> lines = jerobins::common::StringUtil::Split(line, ":");
        if (lines.size() != 2) {

          throw std::runtime_error("Could not deserialize");
        }
        std::string key = lines[0];
        std::string value = lines[1];
        config.Write<std::string>(key, value);
      }
      return config;
    }

    void Configuration::Serialize(std::ostream &output) const {
      for_each(this->mappings.begin(), this->mappings.end(),
               [&output](auto pair) {
                 output << pair.first << ":" << pair.second << std::endl;
               });
      output.flush();
    }
  }
}
