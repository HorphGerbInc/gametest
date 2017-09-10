

#include <Engine/Engine.hpp>

namespace jerobins {
  namespace engine {

    Engine::Engine(Configuration configuration) {}

    void Render(std::vector<IRenderable> objects) {
      std::for_each(objects.begin(), objects.end(), Render);
    }

    void Render(IRenderable &obj) {
      switch (obj.Type()) {
      case jerobins::render::RenderType.LineLoop:
        break;
      case jerobins::render::RenderType.Lines:
        break;
      case jerobins::render::RenderType.LinesAdjacency:
        break;
      case jerobins::render::RenderType.LineStrip:
        break;
      case jerobins::render::RenderType.LineStripAdjacency:
        break;
      case jerobins::render::RenderType.Patches:
        break;
      case jerobins::render::RenderType.Points:
        break;
      case jerobins::render::RenderType.TriangleFan:
        break;
      case jerobins::render::RenderType.Triangles:
        break;
      case jerobins::render::RenderType.TrianglesAdjacency:
        break;
      case jerobins::render::RenderType.TriangleStrip:
        break;
      case jerobins::render::RenderType.TriangleStripAdjacency:
        break;
      default:
        // TODO: LOG and continue
        break;
      }
    }
  }
}
