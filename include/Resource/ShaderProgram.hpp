
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

#include <Render/OpenGL.hpp>
#include <Resource/FragmentShader.hpp>
#include <Resource/IResource.hpp>
#include <Resource/VertexShader.hpp>
#include <vector>

namespace jerobins {
  namespace resource {
    class ShaderProgram : public IResource<ShaderProgram> {
    public:
      static ShaderProgram Load(std::string filename);

      // Activate program on GPU
      void Attach();
      // Deactivate program on GPU
      void Detach();

      // Link all shaders to the program
      void Link();

      // Return the string representation of the program
      virtual std::string ToString() const;

      std::string Name() const { return name; }
      std::string Version() const { return version; }
      std::string Description() const { return description; }

      std::vector<VertexShader> vertexShaders;
      std::vector<FragmentShader> fragmentShaders;

      ShaderProgram();

    private:
      bool active = false;
      GLint programID = 0;
      std::string version;
      std::string name;
      std::string description;
    };
  }
}

#endif