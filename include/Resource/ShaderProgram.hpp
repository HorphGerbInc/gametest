
#ifndef _SHADERPROGRAM_HPP__
#define _SHADERPROGRAM_HPP__

#include <Render/OpenGL.hpp>
#include <Resource/FragmentShader.hpp>
#include <Resource/IResource.hpp>
#include <Resource/VertexShader.hpp>
#include <vector>

namespace jerobins {
  namespace resource {

    /**
     * @brief Shader program.
     *
     */
    class ShaderProgram : public IResource<ShaderProgram> {
    public:
      /**
       * @brief Load the shader from a file.
       *
       * @param filename        File to lod from.
       * @return ShaderProgram  Loaded shader program.
       */
      static ShaderProgram Load(std::string filename);

      /**
       * @brief Attach the program and make it active.
       *
       */
      void Attach() const;

      /**
       * @brief Detach the program and make it inactive.
       *
       */
      void Detach() const;

      /**
       * @brief Link the shaders to this program.
       *
       */
      void Link();

      /**
       * @brief Return the string representation of the program.
       *
       * @return std::string  String representation.
       */
      virtual std::string ToString() const;

      /**
       * @brief Return the name of the program.
       *
       * @return std::string The name of the program.
       */
      std::string Name() const { return name; }

      /**
       * @brief Return the version of the program.
       *
       * @return std::string Program version.
       */
      std::string Version() const { return version; }

      /**
       * @brief Return the description of the program.
       *
       * @return std::string Program description.
       */
      std::string Description() const { return description; }

      /**
       * @brief List of vertex shaders.
       *
       */
      std::vector<VertexShader> vertexShaders;

      /**
       * @brief List of fragment shaders.
       *
       */
      std::vector<FragmentShader> fragmentShaders;

      /**
       * @brief Create a new shader program.
       *
       */
      ShaderProgram();

    private:
      bool active = false;
      GLint programID = 0;
      std::string version;
      std::string name;
      std::string description;
    };
  } // namespace resource
} // namespace jerobins

#endif