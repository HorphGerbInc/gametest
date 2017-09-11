
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <vector>

#include <Common/Configuration.hpp>
#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace engine {

    class Engine {
    private:
      Engine();

    public:
      Engine(jerobins::common::Configuration configuration);

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