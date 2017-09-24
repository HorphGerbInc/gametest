
#ifndef VERTEXSHADER_HPP_
#define VERTEXSHADER_HPP_

#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {
    class VertexShader : public Shader<VertexShader,ShaderType::Vertex> {
    public:

      VertexShader(std::string name, std::string description, std::string version, std::string contents);

      // Compile the shader
      virtual bool Compile();
      
      // Load the shader from a file.
      static VertexShader Load(std::string filename);

      // Save the shader to a file
      void Save(std::string filename);

    };
  }
}

#endif