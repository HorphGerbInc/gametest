
#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <map>
#include <string>
#include <vector>

#include <Common/StringUtil.hpp>
#include <Common/Util.hpp>
#include <Common/Version.hpp>

namespace jerobins {
  namespace common {

    /**
     * @brief Holds the runtime configuration of the application.
     *
     */
    class Configuration {
    private:
      // The key-value mappings.
      std::map<std::string, char *> mappings;

    public:
      /**
       * @briefThe current configuration version.
       *
       */
      const static jerobins::common::Version Version;

      /**
       * @brief Create an empty configuration.
       *
       */
      Configuration();

      /**
       * @brief Copy an existing configuration.
       *
       * @param other The configuration to copy.
       */
      Configuration(const Configuration &other);

      /**
       * @brief                 Copy an existing configuration.
       *
       * @param other           The configuration to copy.
       * @return Configuration& Return a reference to ourselves.
       */
      Configuration &operator=(const Configuration &other);
      /**
       * @brief Read the value of a property.
       *
       * @detailed Read the value of the property if it exists.  If the
       * configuration does not have the specified property and exception is
       * thrown.
       *
       * @tparam T    The value type.
       * @param key   The property of interest.
       * @return T    The value of the property.
       */
      template <typename T> T Read(std::string key) {
        auto iter = mappings.find(key);
        if (iter == mappings.end()) {
          throw std::exception("Configuration key not found: " + key);
        }
        return jerobins::common::Convert<T>(iter->second);
      }

      /**
       * @brief Set   the value of a property.
       *
       * @tparam T    The value type.
       * @param key   The property name.
       * @param value The property value.
       */
      template <typename T> void Write(std::string key, T value) {
        Delete(key);

        auto valueBytes = new char[sizeof(T)];
        auto ptr = &value;
        std::fill(ptr, ptr + sizeof(T), valueBytes);
        mappings.insert(std::pair<std::string, char *>(key, valueBytes));
      }

      /**
       * @brief Remove the property from the configuration.
       *
       * @param key The name of the property.
       */
      void Delete(std::string key);

      /**
       * @brief Create a new configuration from a stream.
       *
       * @param input           The input stream which contains the
       * configuration.
       * @return Configuration  The constructed configuration.
       */
      static Configuration Deserialize(std::istream &input);

      /**
       * @brief Write the configuration out to a stream.
       *
       * @param output  The stream to write to.
       */
      void Serialize(std::ostream &output) const;
    };
  } // namespace common
} // namespace jerobins
#endif