
// StdLib
#include <fstream>
#include <iostream>

// Jerobins
#include <Common/StringUtil.hpp>
#include <Resource/ShaderProgram.hpp>
// Lib
#include <Resource/Json.hpp>

namespace jerobins {
  namespace resource {

    ShaderProgram ShaderProgram::Load(std::string filename) {
      nlohmann::json program = LoadJson(filename);
      ShaderProgram result;

      jerobins::resource::ThrowIfFieldNotSet(program, "version");
      jerobins::resource::ThrowIfFieldNotSet(program, "name");
      jerobins::resource::ThrowIfFieldNotSet(program, "description");
      jerobins::resource::ThrowIfFieldNotSet(program, "vertexShaders");
      jerobins::resource::ThrowIfFieldNotSet(program, "fragmentShaders");

      std::string version = program["version"];
      std::string name = program["name"];
      std::string description = program["description"];
      std::vector<std::string> vertexShaders = program["vertexShaders"].get<std::vector<std::string>>();
      std::vector<std::string> fragmentShaders = program["fragmentShaders"].get<std::vector<std::string>>();

      result.version = version;
      result.name = name;
      result.description = description;
      result.name = name;

      for (auto fragShader : fragmentShaders) {
        result.fragmentShaders.push_back(
            jerobins::resource::FragmentShader::Load(fragShader));
      }
      for (auto vertShader : vertexShaders) {
        result.vertexShaders.push_back(
            jerobins::resource::VertexShader::Load(vertShader));
      }

      return result;
    }

    ShaderProgram::ShaderProgram() {
      programID = glCreateProgram();
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

    void ShaderProgram::Link() {
      if(programID) return;
      for(auto vert : vertexShaders) {
        vert.Compile();
        glAttachShader(programID, vert.ShaderId());        
      }
      for(auto frag : fragmentShaders) {
        frag.Compile();
        glAttachShader(programID, frag.ShaderId());        
      }
      glLinkProgram(programID);      
    }
  }
}