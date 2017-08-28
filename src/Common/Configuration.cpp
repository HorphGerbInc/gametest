
#include <Common/Configuration.hpp>

namespace jerobins
{
namespace common
{

const jerobins::common::Version Configuration::Version(0, 1, 0);
    

Configuration::Configuration()
{
    /* Empty */
}

// Create a configuration object from another
Configuration::Configuration(const Configuration &other) : mappings(other.mappings)
{
    /* Empty */
}

Configuration &Configuration::operator = (const Configuration &other)
{
    return *this;
}

// Remove the configuration value
void Configuration::Delete(std::string key)
{
    auto iter = mappings.find(key);
    if (iter != mappings.end())
    {
        delete iter->second;
        mappings.erase(iter);
    }
}

static Configuration Deserialize(std::istream &input)
{
    return Configuration();
}

void Configuration::Serialize(std::ostream &output) const
{
}


}
}
