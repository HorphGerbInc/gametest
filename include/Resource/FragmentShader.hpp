
#ifndef FRAGMENTSHADER_HPP_
#define FRAGMENTSHADER_HPP_

#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {
    class FragmentShader : public Shader<FragmentShader, ShaderType::Fragment> {
    public:
      FragmentShader(std::string name, std::string description,
                     std::string version, std::string contents);

      virtual bool Compile();

      // Load the shader from a file.
      static FragmentShader Load(std::string filename);

      // Save the shader to a file
      void Save(std::string filename);
    };
  }
}

#endif