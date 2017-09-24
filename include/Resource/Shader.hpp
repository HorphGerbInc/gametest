
#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#if defined(_WIN32)
// #include <windows.h>
#endif

#include <vector>

#include <Common/IString.hpp>
#include <Common/Version.hpp>
#include <Render/OpenGL.hpp>
#include <Resource/IResource.hpp>

namespace jerobins {
  namespace resource {

    enum ShaderType { Vertex, Fragment };

    template <class Derived, ShaderType type>
    class Shader : public jerobins::resource::IResource<Derived> {
    public:
      // Return shader name
      std::string Name() const { return name; }

      // Return shader description
      std::string Description() const { return description; }

      // Return shader contents
      std::string Content() const { return content; }

      // Length of the shader
      std::size_t Length() const { return content.size(); }

      // Compile the shader
      virtual bool Compile() = 0;

      ShaderType GetType() const { return type; };

      // Return a string representation
      virtual std::string ToString() const { return description; }

    protected:
      bool compile(GLenum shaderType) {
        // create shader
        shaderId = glCreateShader(shaderType);
        const char *str = content.c_str();
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

        return true;
      }

    private:
      GLuint shaderId;
      std::string name;
      std::string description;
      std::string content;
    };
  }
}

#endif