
// STL
#include <fstream>
#include <streambuf>

// lib
#include <json.hpp>

// Mine
#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {

    Shader::Shader(std::string fileContents) { this->content = fileContents; }

    Shader::Shader(Shader &&other) {
      this->content = other.content;
      other.content = "";
    }

    Shader &Shader::operator=(Shader &&other) {
      this->content = other.content;
      return *this;
    }

    std::string Shader::Content() const { return this->content; }

    size_t Shader::Length() const { return this->content.length(); }

    std::string Shader::ToString() const { return Content(); }

    bool Shader::Compile(ShaderType type) {
      GLenum shaderType = GL_VERTEX_SHADER;
      switch (type) {
      case jerobins::resource::ShaderType::Vertex:
        shaderType = GL_VERTEX_SHADER;
        break;
      case jerobins::resource::ShaderType::Fragment:
        shaderType = GL_FRAGMENT_SHADER;
        break;
      default:
        throw std::runtime_error("Invalid shader type");
      };

      // create shader
      shaderId = glCreateShader(shaderType);
      glShaderSource(shaderId, 1, content.c_str(), nullptr);

      // compile shader
      glCompileShader(shaderId);

      // check shader
      int success = 0;
      glGetShader(shaderId, GL_COMPILE_STATUS, &success);
      if (!success) {
        char error[512];
        glGetShaderInfoLog(shaderId, 512, NULL, error);
        throw std::runtime_error(std::string(error));
      }

      return false;
    }

    Shader Shader::Load(std::string filename) {
      std::ifstream input(filename);
      json j;
      input >> j;
      std::string version = input["version"];
      std::string name = input["name"];
      std::string contents = input["contents"];
      std::list deps = input["dependencies"];
      return Shader(str);
    }
  }
}