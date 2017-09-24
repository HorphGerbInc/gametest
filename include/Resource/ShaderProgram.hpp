
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

#include <vector>
#include <Render/OpenGL.hpp>
#include <Resource/IResource.hpp>
#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {
    class ShaderProgram : public IResource<ShaderProgram> {
    public:
      static ShaderProgram Load(std::string filename);

      bool Compile();

      // Activate program on GPU
      void Attach();
      // Deactivate program on GPU
      void Detach();

      virtual std::string ToString() const;

      std::string version;
      std::string name;
      std::string description;
      //std::vector<Shader> shaders;

    private: 
      bool active = false;
      GLint programID;
    };
  }
}

#endif