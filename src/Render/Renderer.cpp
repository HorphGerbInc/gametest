
#include <Render/Renderer.hpp>
#include <Math/Vec2.hpp>

namespace jerobins {
  namespace render {
      
    Renderer::Renderer() {}

    void Renderer::Render(std::vector<jerobins::render::IRenderable> objects) {
      auto iter = objects.begin();
      while (iter != objects.end()) {
        Render(*iter);
        ++iter;
      }
    }

    void Renderer::Render(jerobins::render::IRenderable &obj) {
		glBindVertexArray(obj.GetVertexArray());
		glBindBuffer(GL_ARRAY_BUFFER, obj.GetBuffer());

		size_t buffer_ofs = 0;

		glBufferSubData(GL_ARRAY_BUFFER, buffer_ofs, sizeof(jerobins::math::Vec2) * obj.VertexCount(), obj.GetVertices());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(jerobins::math::Vec2), ((uint8_t *)0) + buffer_ofs);
		buffer_ofs += sizeof(jerobins::math::Vec2) * obj.VertexCount();

      // Load array
      switch (obj.Type()) {
      case jerobins::render::RenderType::LineLoop:
        break;
      case jerobins::render::RenderType::Lines:
        break;
      case jerobins::render::RenderType::LinesAdjacency:
        break;
      case jerobins::render::RenderType::LineStrip:
        break;
      case jerobins::render::RenderType::LineStripAdjacency:
        break;
      case jerobins::render::RenderType::Patches:
        break;
      case jerobins::render::RenderType::Points:
        break;
      case jerobins::render::RenderType::TriangleFan:
        break;
      case jerobins::render::RenderType::Triangles:
		  glDrawArrays(GL_TRIANGLES, 0 , obj.VertexCount());
        break;
      case jerobins::render::RenderType::TrianglesAdjacency:
        break;
      case jerobins::render::RenderType::TriangleStrip:
        break;
      case jerobins::render::RenderType::TriangleStripAdjacency:
        break;
      default:
        // TODO: LOG and continue
        break;
      }
    }
  }
}