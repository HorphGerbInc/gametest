
#ifndef JSON_HPP_
#define JSON_HPP_

#include <json.hpp>
#include <string>

namespace jerobins {
  namespace resource {
    nlohmann::json LoadJson(std::string filename);
    void ThrowIfFieldNotSet(const nlohmann::json &doc, const std::string &field);
  }
}

#endif