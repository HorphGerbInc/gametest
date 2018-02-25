
#ifndef FRAGMENTSHADER_HPP_
#define FRAGMENTSHADER_HPP_

#include <Resource/Shader.hpp>

namespace jerobins {
  namespace resource {
    /**
     * @brief Holds information about a fragment shader.
     * 
     */
    class FragmentShader : public Shader<FragmentShader, ShaderType::Fragment> {
    public:
      /**
       * @brief
       *
       * @param name          Name of the fragment shader.
       * @param description   Description of the fragment shader.
       * @param version       Version of the fragment shader.
       * @param contents      Fragment shader code.
       */
      FragmentShader(std::string name, std::string description,
                     std::string version, std::string contents);

      /**
       * @brief Compile the fragment shader.
       *
       * @return true   If successfull.
       * @return false  If failed.
       */
      virtual bool Compile();

      /**
       * @brief Load a shader from a file.
       *
       * @param filename        File to load from.
       * @return FragmentShader The loaded fragment shader.
       */
      static FragmentShader Load(std::string filename);

      /**
       * @brief Save the fragment shader to a file.
       *
       * @param filename The file to save to.
       */
      void Save(std::string filename);
    };
  } // namespace resource
} // namespace jerobins

#endif