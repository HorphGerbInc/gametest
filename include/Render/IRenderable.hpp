
#ifndef _IRENDERABLE_HPP_
#define _IRENDERABLE_HPP_

#include <Render/RenderType.hpp>

namespace jerobins {
  namespace render {
    class IRenderable {
    public:

      virtual std::vector<float> GetData() = 0;
      virtual std::vector<int> GetAdja() = 0;
      virtual RenderType Type() const = 0;
      virtual bool UseAdjacency() const = 0;

    };
  }
}

#endif