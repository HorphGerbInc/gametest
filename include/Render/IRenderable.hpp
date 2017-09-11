
#ifndef _IRENDERABLE_HPP_
#define _IRENDERABLE_HPP_

#include <Render/RenderType.hpp>

namespace jerobins {
  namespace render {
    class IRenderable {
    public:
      // Raw underlying data
      virtual const float *Data() const = 0;
      virtual std::size_t DataCount() const = 0;

      // Indices, if specified, null if not.
      virtual const std::size_t *Indices() const = 0;
      virtual std::size_t IndicesCount() const = 0;

      // The structure of the data
      virtual RenderType Type() const = 0;
    };
  }
}

#endif