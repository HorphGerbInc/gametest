
#ifndef _IRENDERABLE_HPP_
#define _IRENDERABLE_HPP_

#include <Render/RenderType.hpp>

#include <Math/Vec2.hpp>
#include <Math/Vec3.hpp>
#include <Math/Vec4.hpp>
#include <Render/Color.hpp>

namespace jerobins {
  namespace render {
    class IRenderable {
    public:
      // Raw underlying data
      virtual const jerobins::math::Vec3<float> *GetVertices() const = 0;
      virtual unsigned int VertexCount() const = 0;

      // Color of vertices
      virtual const Color *GetColors() const = 0;
      virtual unsigned int ColorCount() const = 0;

      // normal of vertices
      virtual const jerobins::math::Vec3<float> *GetNormals() const = 0;
      virtual unsigned int NormalCount() const = 0;

      // Textures
      virtual const jerobins::math::Vec2<int> *GetTexureCoords() const = 0;
      virtual unsigned int TextureCount() const = 0;

      // Indices
      virtual const int *GetIndices() const = 0;
      virtual unsigned int IndicesCount() const = 0;

      // The structure of the data
      virtual RenderType Type() const = 0;

    };
  }
}

#endif