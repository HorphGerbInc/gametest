
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <vector>

#include <Render/OpenGL.hpp>

#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace render {
    class Renderer {
    public:
      /**
       * @brief Create a new Renderer.
       *
       */
      Renderer();

      /**
       * @brief Initialize rendering system, create buffer, load programs.
       *
       */
      void Init();

      /**
       * @brief Given a list of renderable objects render them.
       *
       * @param objs List of renderable objects.
       */
      void Render(std::vector<jerobins::render::IRenderable> objs);

      /**
       * @brief Given a renderable object render it to the screen.
       *
       * @param obj The renderable object.
       */
      void Render(jerobins::render::IRenderable &obj);

    protected:
      GLint vertexAttrPtr;
      GLint colorAttrPtr;
      GLint normalAttrPtr;
      GLint textureAttrPtr;

      GLuint VertexArrayID;
      GLuint vertexbuffer;
    };
  } // namespace render
} // namespace jerobins

#endif