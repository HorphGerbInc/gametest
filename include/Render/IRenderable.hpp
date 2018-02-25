
#ifndef _IRENDERABLE_HPP_
#define _IRENDERABLE_HPP_

#include <Render/RenderType.hpp>

#include <Math/Vec2.hpp>
#include <Math/Vec3.hpp>
#include <Math/Vec4.hpp>
#include <Render/Color.hpp>

#include <Resource/ShaderProgram.hpp>

namespace jerobins {
  namespace render {
    /**
     * @brief Base class for all renderable objects.
     *
     */
    class IRenderable {
    public:
      /**
       * @brief Return the list of vectices representing the object.
       *
       * @return const jerobins::math::Vec3<float>*
       */
      virtual const jerobins::math::Vec3<float> *GetVertices() const = 0;

      /**
       * @brief How many vectices used to represent the object.
       *
       * @return unsigned int Number of vectices.
       */
      virtual unsigned int VertexCount() const = 0;

      /**
       * @brief Color of each vertex.
       *
       * @return const Color* The array of colors.
       */
      virtual const Color *GetColors() const = 0;
      /**
       * @brief Number of colors.  Also the number of vectices.
       *
       * @return unsigned int Number of colors.
       */
      virtual unsigned int ColorCount() const = 0;

      /**
       * @brief Normals for each vectex.
       *
       * @return const jerobins::math::Vec3<float>* Array of normals.
       */
      virtual const jerobins::math::Vec3<float> *GetNormals() const = 0;

      /**
       * @brief The number of normals.  Same as the number of vertices.
       *
       * @return unsigned int Number of normals.
       */
      virtual unsigned int NormalCount() const = 0;

      /**
       * @brief Texture coordinates.
       *
       * @return const jerobins::math::Vec2<int>* Texture coordinates.
       */
      virtual const jerobins::math::Vec2<int> *GetTexureCoords() const = 0;

      /**
       * @brief Number of texture coordinates.
       *
       * @return unsigned int Number of texture coordinates.
       */
      virtual unsigned int TextureCount() const = 0;

      /**
       * @brief Indices if using indexed vectex.
       *
       * @return const int* Array of indices.
       */
      virtual const int *GetIndices() const = 0;

      /**
       * @brief Number of indices.
       *
       * @return unsigned int Number of indices.
       */
      virtual unsigned int IndicesCount() const = 0;

      /**
       * @brief Get the render type of the object.
       *
       * @detailed This controls how vertices are rendered.  It also allows the
       * renderer to know if we are using indices or not.
       *
       * @return RenderType Render type.
       */
      virtual RenderType Type() const = 0;

      /**
       * @brief The shader program used by this object.
       *
       * @return const jerobins::resource::ShaderProgram Shader program used by
       * this object.
       */
      virtual const jerobins::resource::ShaderProgram Program() const = 0;
    };
  } // namespace render
} // namespace jerobins

#endif