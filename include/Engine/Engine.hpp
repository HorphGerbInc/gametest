
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <Common/Configuration.hpp>
#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace engine {
    class Engine {
    private:
      Engine();

    public:
      Engine(Configuration configuration);

      /*
       *  Given a list of polygons we render them
       */
      void RenderPolygons(std::vector<Polygon> polygons);

      /*
       *  Given a polygon we want to render it to the screen
       */
      void RenderPolygon(Polygon &poly);
    };
  }
}

#endif