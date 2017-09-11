
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <vector>

#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace render {
    class Renderer {
    public:

      Renderer();
      /*
       *  Given a list of polygons we render them
       */
      void Render(std::vector<jerobins::render::IRenderable> objs);

      /*
       *  Given a polygon we want to render it to the screen
       */
      void Render(jerobins::render::IRenderable &poly);
    };
  }
}

#endif