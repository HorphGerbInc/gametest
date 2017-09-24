
// StdLib
#include <fstream>
#include <iostream>

// Jerobins
#include <Common/StringUtil.hpp>
#include <Resource/ShaderProgram.hpp>
// Lib
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
      //result.vertexShaders = vertexShaders;
      //result.fragmentShaders = fragmentShaders;
      result.name = name;

      /*
      for (auto fragShader : fragmentShaders) {
        result.AddFragmentShader(fragShader);
      }
      for (auto vertShader : vertexShaders) {
        result.AddVertexShader(vertShader);
      }
      */

      return result;
    }

    std::string ShaderProgram::ToString() const { return this->name; }

    void ShaderProgram::Attach() {
      if (active)
        return;
      glUseProgram(programID);
      active = true;
    }

    void ShaderProgram::Detach() {
      glUseProgram(0);
      active = false;
    }

  }
}