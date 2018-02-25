
#ifndef JSON_HPP_
#define JSON_HPP_

#include <json.hpp>
#include <string>

namespace jerobins {
  namespace resource {

    /**
     * @brief Load JSON from a file.
     *
     * @param filename          File to load contents from.
     * @return nlohmann::json   JSON object.
     */
    nlohmann::json LoadJson(std::string filename);

    /**
     * @brief Validate a field is set.
     *
     * @param doc     JSON document to check for field.
     * @param field   Name of the field.
     */
    void ThrowIfFieldNotSet(const nlohmann::json &doc,
                            const std::string &field);
  } // namespace resource
} // namespace jerobins

#endif