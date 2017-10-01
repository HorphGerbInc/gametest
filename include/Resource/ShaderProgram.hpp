
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

#include <vector>
#include <Render/OpenGL.hpp>
#include <Resource/IResource.hpp>
#include <Resource/VertexShader.hpp>
#include <Resource/FragmentShader.hpp>

namespace jerobins {
  namespace resource {
    class ShaderProgram : public IResource<ShaderProgram> {
    public:
      static ShaderProgram Load(std::string filename);

      // Activate program on GPU
      void Attach();
      // Deactivate program on GPU
      void Detach();

      void Link();

      virtual std::string ToString() const;

      std::string version;
      std::string name;
      std::string description;
      std::vector<VertexShader> vertexShaders;
      std::vector<FragmentShader> fragmentShaders;

      ShaderProgram();
      
    private: 
      bool active = false;
      GLint programID;
    };
  }
}

#endif