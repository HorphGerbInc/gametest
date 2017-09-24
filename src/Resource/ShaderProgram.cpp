
#include <iostream>
#include <fstream>

#include <Resource/ShaderProgram.hpp>
#include <json.hpp>

namespace jerobins {
  namespace resource {

    ShaderProgram::ShaderProgram(std::string name) {
        this->name = name;
    }
    
    ShaderProgram ShaderProgram::Load(std::string filename) {
      std::ifstream input(filename);
      nlohmann::json program;
      input >> program;
      std::cout << program["version"] << std::endl;
      std::cout << program["name"] << std::endl;
      std::cout << program["description"] << std::endl;
      std::cout << program["vertexShaders"] << std::endl;
      std::cout << program["fragmentShaders"] << std::endl;

      std::string name = program["name"];
      ShaderProgram result(name);
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