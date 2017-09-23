
#ifndef _IRENDERABLE_HPP_
#define _IRENDERABLE_HPP_

#include <Render/RenderType.hpp>

namespace jerobins {
  namespace render {
    class IRenderable {
    public:
      // Raw underlying data
      virtual const float *GetVertices() const = 0;
      virtual std::size_t VertexCount() const = 0;

      // Indices, if specified, null if not.
      virtual const std::size_t *Indices() const = 0;
      virtual std::size_t IndicesCount() const = 0;

	  int GetVertexArray() { return vertexArray; }
	  int GetBuffer() { return buffer; }

      // The structure of the data
      virtual RenderType Type() const = 0;
	protected:
		int vertexArray;
		int buffer;
	};
  }
}

#endif