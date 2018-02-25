
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

    /**
     * @brief Return a string representation of the enum.
     *
     * @param type          RenderType value.
     * @return std::string  String representation of enum value.
     */
    std::string RenderTypeToString(RenderType type);

    /**
     * @brief Convert a string representation of RenderType to its enum value..
     *
     * @param str           String representation of RenderType value.
     * @return RenderType   RenderType value.
     */
    RenderType StringToRenderType(const std::string &str);

    /**
     * @brief Convert RenderType to OpenGL type.
     *
     * @param type    RenderType value.
     * @return GLint  OpenGL value.
     */
    GLint RenderTypeToGLType(RenderType type);
  } // namespace render
} // namespace jerobins

#endif