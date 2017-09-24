
#ifndef _RENDERTYPE_HPP_
#define _RENDERTYPE_HPP_

#include <Render/OpenGL.hpp>

namespace jerobins {
  namespace render {
    enum RenderType {
      LineLoop,
      Lines,
      LinesAdjacency,
      LineStrip,
      LineStripAdjacency,
      Patches,
      Points,
      TriangleFan,
      Triangles,
      TrianglesAdjacency,
      TriangleStrip,
      TriangleStripAdjacency,
    };

    static GLint RenderTypeToGLType(RenderType type) {
      switch (type) {
      case RenderType::LineLoop:
        return GL_LINE_LOOP;
      case RenderType::Lines:
        return GL_LINES;
      case RenderType::LinesAdjacency:
        return GL_LINES_ADJACENCY;
      case RenderType::LineStrip:
        return GL_LINE_STRIP;
      case RenderType::LineStripAdjacency:
        return GL_LINE_STRIP_ADJACENCY;
      case RenderType::Patches:
        return GL_PATCHES;
      case RenderType::Points:
        return GL_POINTS;
      case RenderType::TriangleFan:
        return GL_TRIANGLE_FAN;
      case RenderType::Triangles:
        return GL_TRIANGLES;
      case RenderType::TrianglesAdjacency:
        return GL_TRIANGLES_ADJACENCY;
      case RenderType::TriangleStrip:
        return GL_TRIANGLE_STRIP;
      case RenderType::TriangleStripAdjacency:
        return GL_TRIANGLE_STRIP_ADJACENCY;
      default:
        return GL_INVALID_ENUM;
      }
    }
  }
}

#endif