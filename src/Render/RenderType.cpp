#include <algorithm>
#include <map>

#include <Render/RenderType.hpp>

namespace jerobins {
  namespace render {

    template <class Input, class Output>
    static Output Get(std::map<Input, Output> &map, Input key, Output result) {
      auto iter = map.find(key);
      if (iter != map.end()) {
        result = iter->second;
      }
      return result;
    }

    std::string RenderTypeToString(RenderType type) {

      static std::map<RenderType, std::string> mappings = {
          {LineLoop, "LineLoop"},
          {Lines, "Lines"},
          {LinesAdjacency, "LinesAdjacency"},
          {LineStrip, "LineStrip"},
          {LineStripAdjacency, "LineStripAdjacency"},
          {Patches, "Patches"},
          {Points, "Points"},
          {TriangleFan, "TriangleFan"},
          {Triangles, "Triangles"},
          {TrianglesAdjacency, "TrianglesAdjacency"},
          {TriangleStrip, "TriangleStrip"},
          {TriangleStripAdjacency, "TriangleStripAdjacency"},
          {Invalid, "Invalid"}};

      return Get(mappings, type, std::string("Invalid"));
    }

    // Convert a string to RenderType
    RenderType StringToRenderType(const std::string &str) {

      static std::map<std::string, RenderType> mappings = {
          {"lineloop", LineLoop},
          {"lines", Lines},
          {"linesadjacency", LinesAdjacency},
          {"linestrip", LineStrip},
          {"linestripadjacency", LineStripAdjacency},
          {"patches", Patches},
          {"points", Points},
          {"trianglefan", TriangleFan},
          {"triangles", Triangles},
          {"trianglesadjacency", TrianglesAdjacency},
          {"trianglestrip", TriangleStrip},
          {"trianglestripadjacency", TriangleStripAdjacency},
          {"invalid", Invalid}};

      std::string key = str;
      std::transform(key.begin(), key.end(), key.begin(), ::tolower);
      return Get(mappings, key, Invalid);
    }

    GLint RenderTypeToGLType(RenderType type) {

      static std::map<RenderType, GLint> mappings = {
          {LineLoop, GL_LINE_LOOP},
          {Lines, GL_LINES},
          {LinesAdjacency, GL_LINES_ADJACENCY},
          {LineStrip, GL_LINE_STRIP},
          {LineStripAdjacency, GL_LINE_STRIP_ADJACENCY},
          {Patches, GL_PATCHES},
          {Points, GL_POINTS},
          {TriangleFan, GL_TRIANGLE_FAN},
          {Triangles, GL_TRIANGLES},
          {TrianglesAdjacency, GL_TRIANGLES_ADJACENCY},
          {TriangleStrip, GL_TRIANGLE_STRIP},
          {TriangleStripAdjacency, GL_TRIANGLE_STRIP_ADJACENCY},
          {Invalid, GL_INVALID_ENUM}};

      return Get(mappings, type, GL_INVALID_ENUM);
    }
  }
}