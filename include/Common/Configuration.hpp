
#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <map>
#include <string>
#include <vector>

#include <Common/Util.hpp>
#include <Common/Version.hpp>
#include <Common/StringUtil.hpp>

namespace jerobins
{
namespace common
{
class Configuration
{
  private:
    std::map<std::string, char*> mappings;

  public:
    const static jerobins::common::Version Version;
    

    Configuration();

    // Create a configuration object from another
    Configuration(const Configuration &other);

    // Assignment
    Configuration &operator= (const Configuration &other);

    // Read configuration value
    template <typename T>
    T Read(std::string key)
    {
        auto iter = mappings.find(key);
        if (iter == mappings.end())
        {
            throw std::exception("Configuration key not found: " + key);
        }
        return jerobins::common::Convert<T>(iter->second);
    }

    // Set the configuration value
    template <typename T>
    void Write(std::string key, T value)
    {
        Delete(key);

        auto valueBytes = new char[sizeof(T)];
        auto ptr = &value;
        std::fill(ptr, ptr + sizeof(T), valueBytes);
        mappings.insert(std::pair<std::string, char*>(key, valueBytes));
    }

    // Remove the configuration value
    void Delete(std::string key);

	static Configuration Deserialize(std::istream &input);

    void Serialize(std::ostream &output) const;
};
}
}
#endif