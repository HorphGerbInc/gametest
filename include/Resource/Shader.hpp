
#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <Common/IString.hpp>
#include <Resource/IResource.hpp>

namespace jerobins {
  namespace resource {

    enume ShaderType{Vertex, Fragment};

    class Shader : public jerobins::resource::IResource<Shader> {
    public:
      Shader(Shader &&other);

      // Return shader contents
      std::string Content() const;
      // Length of the shader
      size_t Length() const;

      // Compile the shader
      bool Compile();

      // Return a string representation
      virtual std::string ToString() const;

      // Load the shader from a file.
      static Shader Load(std::string filename);

      // Save the shader to a file
      void Save(std::string filename);

      Shader &operator=(Shader &&other);

    private:
      std::list<std::string> dependencies;
      Shader(std::string);
      std::string content;
      unsigned int shaderId;
    };
  }
}

#endif