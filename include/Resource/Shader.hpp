
#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <windows.h>

#define GL_GLEXT_PROTOTYPES 1

// jerobins: This MUST be before GL/gl.h
#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glext.h>

#include <vector>

#include <Common/IString.hpp>
#include <Common/Version.hpp>
#include <Resource/IResource.hpp>

namespace jerobins {
  namespace resource {

    enum ShaderType { Vertex, Fragment };

    class Shader : public jerobins::resource::IResource<Shader> {
    public:
      Shader(const Shader &&other);

      // Return shader contents
      std::string Content() const;
      // Length of the shader
      size_t Length() const;

      // Compile the shader
      bool Compile(ShaderType type);

      // Return a string representation
      virtual std::string ToString() const;

      // Load the shader from a file.
      static Shader Load(std::string filename);

      // Save the shader to a file
      void Save(std::string filename);

      Shader &operator=(Shader &&other);

    private:
      std::vector<std::string> dependencies;
      Shader(jerobins::common::Version, std::string, std::vector<std::string>);
      jerobins::common::Version version;
      std::string content;
      unsigned int shaderId;
    };
  }
}

#endif