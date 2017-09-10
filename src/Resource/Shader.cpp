
// STL
#include <fstream>
#include <streambuf>
#include <sstream>

// lib
#include <json.hpp>

// Mine
#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {

    Shader::Shader(jerobins::common::Version version, std::string content, std::vector<std::string> deps) : version(version), content(content), dependencies(deps) {}

    Shader::Shader(const Shader &&other) : version(other.version), content(other.content), dependencies(other.dependencies) {
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
      const char* str = content.c_str();
      glShaderSource(shaderId, 1, &str, NULL);

      // compile shader
      glCompileShader(shaderId);

      // check shader
      int success = 0;
      glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
      if (!success) {
        char error[512];
        glGetShaderInfoLog(shaderId, 512, NULL, error);
        throw std::runtime_error(std::string(error));
      }

      return false;
    }

    Shader Shader::Load(std::string filename) {
      std::ifstream input(filename);
      nlohmann::json j;
      input >> j;
      std::string versionString = j["version"];
      std::string name = j["name"];
      std::string content = j["content"];
      std::vector<std::string> deps = j["dependencies"];

      std::stringstream ss;
      ss << versionString;
      auto version = jerobins::common::Version::Deserialize(
          ss, jerobins::common::SerializationFormat::Text);

      return Shader(version, content, deps);
    }
  }
}