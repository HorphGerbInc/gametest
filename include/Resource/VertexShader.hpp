
#ifndef VERTEXSHADER_HPP_
#define VERTEXSHADER_HPP_

#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {
    class VertexShader : public Shader<VertexShader, ShaderType::Vertex> {
    public:
      /**
       * @brief Create a vertex
       *
       * @param name          The name of the vertex shader.
       * @param description   The description of the vertex shader.
       * @param version       Vertex shader version.
       * @param contents      Vertex shader code.
       */
      VertexShader(std::string name, std::string description,
                   std::string version, std::string contents);

      // Compile the vertex shader.
      virtual bool Compile();

      // Load the shader from a file.
      static VertexShader Load(std::string filename);

      // Save the shader to a file
      void Save(std::string filename);
    };
  } // namespace resource
} // namespace jerobins

#endif