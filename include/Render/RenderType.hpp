
#ifndef _RENDERTYPE_HPP_
#define _RENDERTYPE_HPP_

#include <string>

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
      Invalid
    };

    std::string RenderTypeToString(RenderType type);
    RenderType StringToRenderType(const std::string &str);
    GLint RenderTypeToGLType(RenderType type);
  }
}

#endif