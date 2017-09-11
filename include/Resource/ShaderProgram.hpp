
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

namespace jerobins {
  namespace resource {
    class ShaderProgram : public IResource<ShaderProgram> {
    public:
      static Load(std::string filename);

      void Attach();
      void Detach();

    private:
      void AddShaderDependency(std::string filename);
      ShaderProgram(std::string filename);
    };
  }
}

#endif