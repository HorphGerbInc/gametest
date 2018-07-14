
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

    /**
     * @brief Shader type.
     *  - Vertex    - Vertex shader.
     *  - Fragment  - Fragment shader.
     */
    enum ShaderType { Vertex, Fragment };

    template <class Derived, ShaderType type>
    class Shader : public jerobins::resource::IResource<Derived> {
    public:
      /**
       * @brief Name of the shader.
       *
       * @return std::string  String representation of the shader.
       */
      std::string Name() const { return name; }

      /**
       * @brief Description of the shader.
       *
       * @return std::string String representation of the shader.
       */
      std::string Description() const { return description; }

      /**
       * @brief Shader content.
       *
       * @return std::string  Content.
       */
      std::string Content() const { return contents; }

      /**
       * @brief The length of the content.
       *
       * @return unsigned int Length of the content.
       */
      unsigned int Length() const { return contents.size(); }

      /**
       * @brief Compile the shader.
       *
       * @return true   Compilation succeeded.
       * @return false  Compilation failed.
       */
      virtual bool Compile() = 0;

      /**
       * @brief Get the type of the shader.
       *
       * @return ShaderType Type of the shader.
       */
      ShaderType GetType() const { return type; };

      /**
       * @brief Convert this resource to a string.
       *
       * @return std::string Return a string representation of shader.
       */
      virtual std::string ToString() const { return description; }

      /**
       * @brief The shaders OpenGL ID.
       *
       * @return GLuint ID.
       */
      GLuint ShaderId() const { return shaderId; }

    protected:
      // Compile the shader for OpenGL.
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
  } // namespace resource
} // namespace jerobins

#endif