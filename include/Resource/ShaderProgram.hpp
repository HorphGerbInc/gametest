
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

#include <Resource/IResource.hpp>

namespace jerobins {
  namespace resource {
    class ShaderProgram : public IResource<ShaderProgram> {
    public:

      static ShaderProgram Load(std::string filename);

      // Activate program on GPU
      void Attach();
      // Deactivate program on GPU
      void Detach();

      virtual std::string ToString() const;

    private:
      std::string name;
      void AddVertexShader(std::string filename);
      void AddFragmentShader(std::string filename);
      ShaderProgram(std::string filename);
    };
  }
}

#endif