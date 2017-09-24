
#ifndef SHADERFACTORY_HPP_
#define SHADERFACTORY_HPP_

// Jerobins
#include <Resource/FragmentShader.hpp>
#include <Resource/VertexShader.hpp>

// Lib
#include <json.hpp>

std::string ReadFile(std::string filename) {
  std::ifstream input(filename);
  std::string content((std::istreambuf_iterator<char>(input)),
                      (std::istreambuf_iterator<char>()));
  return content;
}

namespace jerobins {
  namespace resource {

    template <class T> struct Prefix { std::string Prefix = ""; };
    template <> struct Prefix<VertexShader> {
      std::string Prefix = "shaders/vertex/";
    };
    template <> struct Prefix<FragmentShader> {
      std::string Prefix = "shaders/fragment/";
    };

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


        std::string file = Prefix<ShaderType>().Prefix + name;
        std::string contents = ReadFile(file);
        
        return ShaderType(name, description, version, contents);
      }
    };
  }
}

#endif