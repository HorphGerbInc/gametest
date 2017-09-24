
#include <iostream>
#include <fstream>

#include <Resource/ShaderProgram.hpp>
#include <json.hpp>

namespace jerobins {
  namespace resource {
    
    ShaderProgram ShaderProgram::Load(std::string filename) {
      std::ifstream input(filename);
      nlohmann::json program;
      input >> program;

      std::string version = program["version"];
      std::string name = program["name"];
      std::string description = program["description"];
      std::vector<std::string> vertexShaders = program["vertexShaders"];
      std::vector<std::string> fragmentShaders = program["fragmentShaders"];
 
      ShaderProgram result;
      result.version = version;
      result.name = name;
      result.description = description;
      result.vertexShaders = vertexShaders;
      result.fragmentShaders = fragmentShaders;
      result.name = name;
      
      return result;
    }

    std::string ShaderProgram::ToString() const {
        return this->name;
    }

    void ShaderProgram::Attach() {}

    void ShaderProgram::Detach() {}

    void ShaderProgram::AddFragmentShader(std::string filename) {}
    void ShaderProgram::AddVertexShader(std::string filename) {}
  }
}