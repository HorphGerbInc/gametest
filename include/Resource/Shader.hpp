
#ifndef _SHADER_HPP_
#define _SHADER_HPP_

// StdLib
#include <vector>

// Jerobins
#include <Common/IString.hpp>
#include <Common/Logger.hpp>
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
      std::string Content() const { return contents; }

      // Length of the shader
      unsigned int Length() const { return contents.size(); }

      // Compile the shader
      virtual bool Compile() = 0;

      // Type of Shader (vertex/fragment)
      ShaderType GetType() const { return type; };

      // Return a string representation
      virtual std::string ToString() const { return description; }

      // Shader Id
      GLuint ShaderId() const { return shaderId; }

    protected:
      bool compile(GLenum shaderType) {

        jerobins::common::Logger::GetLogger()->Log("Compiling shader for " +
                                                   Name());
        // create shader
        shaderId = glCreateShader(shaderType);
        const char *str = contents.c_str();
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
        
        jerobins::common::Logger::GetLogger()->Log(
            "sucess compiling shader for " + Name());
        return true;
      }

    protected:
      GLuint shaderId = -1;
      std::string name;
      std::string description;
      std::string contents;
      std::string version;
    };
  }
}

#endif