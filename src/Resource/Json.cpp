#include <fstream>

#include <Resource/Json.hpp>

namespace jerobins {
  namespace resource {
    nlohmann::json LoadJson(std::string filename) {
      std::ifstream input(filename);
      if (input.is_open()) {
        try {
          nlohmann::json result;
          input >> result;
          return result;
        } catch (std::exception &ex) {
          throw std::runtime_error(filename + ": " + ex.what());
        }
      }
      throw std::runtime_error("could not open file " + filename);
    }

    void ThrowIfFieldNotSet(const nlohmann::json & doc,const std::string & field) {
      if(doc.at(field).is_null()) throw std::runtime_error(field + " is null");
    }
    
  }
}