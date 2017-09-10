
#ifndef _RENDERTYPE_HPP_
#define _RENDERTYPE_HPP_

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
  }
}

#endif