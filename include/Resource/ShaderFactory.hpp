
#ifndef SHADERFACTORY_HPP_
#define SHADERFACTORY_HPP_

// Jerobins
#include <Resource/FragmentShader.hpp>
#include <Resource/VertexShader.hpp>

// Lib
#include <Common/Json.hpp>

std::string ReadFile(std::string filename) {
  std::ifstream input(filename);
  std::string content((std::istreambuf_iterator<char>(input)),
                      (std::istreambuf_iterator<char>()));
  return content;
}

namespace jerobins {
  namespace resource {

	  template <typename T>
	  std::string Prefix() {
		  return std::string("");
	  }
	  template <>
	  std::string Prefix<VertexShader>() {
		  return std::string("");
	  }
	  template <>
	  std::string Prefix<FragmentShader>() {
		  return std::string("");
	  }

	  class ShaderFactory {

    public:
      template <class ShaderType>
      static ShaderType LoadShader(std::string filename) {
        std::ifstream input(filename);
        nlohmann::json j;
        input >> j;

        std::string version = j["version"];
        std::string name = j["name"];
        std::string description = j["description"];
        std::string type = j["type"];


        std::string file = Prefix<ShaderType>() + name;
        std::string contents = ReadFile(file);
        
        return ShaderType(name, description, version, contents);
      }
    };
  }
}

#endif