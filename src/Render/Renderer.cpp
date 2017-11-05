#include <sstream>

#include <Common/Logger.hpp>
#include <Math/Vec2.hpp>
#include <Render/Renderer.hpp>

namespace jerobins {
  namespace render {

    Renderer::Renderer() {}

    // Load opengl
    void Renderer::Init() {

      // Initialize OpenGL
      if (!gladLoadGL()) {
        jerobins::common::Logger::GetLogger()->Log(
            "Could not load opengl", jerobins::common::LoggingLevel::Fatal);
        exit(-1);
      }

      // Verify
      if (GLVersion.major != 3 || GLVersion.minor != 0) {
        std::stringstream ss;
        ss << "Expected OpenGL version 4.0, found " << GLVersion.major << "."
           << GLVersion.minor;
        throw std::runtime_error(ss.str());
      }

      // Default background color
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

      // TODO(jerobins): Generated Arrays/Buffers for other components
      // Create and bind a VBO for vertices
      glGenVertexArrays(1, &VertexArrayID);
      glBindVertexArray(VertexArrayID);
      // Generate a buffer for vertices
      glGenBuffers(1, &vertexbuffer);
      // TODO(jerobins): Default for now, determine best practices
      glBufferData(GL_ARRAY_BUFFER, 4098 , NULL, GL_STATIC_DRAW);
      jerobins::common::Logger::GetLogger()->Log("renderer initialized");
    }

    void Renderer::Render(std::vector<jerobins::render::IRenderable> objects) {
      auto iter = objects.begin();
      while (iter != objects.end()) {
        Render(*iter);
        ++iter;
      }
    }

    /*
     * Load:
     *  Vertices
     *  Color
     *  Normals
     *  Textures
     *
     *  1. Load data
     *  2. Enable attribute pointer
     *  3. Update sub buffer offset
     *
     */
    void Renderer::Render(jerobins::render::IRenderable &obj) {

      obj.Program().Attach();
      CheckOpenGLError();

      uint32_t subBufferOffset = 0;

      // Vertices
      GLsizei elementSize = sizeof(jerobins::math::Vec3<float>);

      // Target type, first index, how many (bytes), data
      glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
      CheckOpenGLError();
      glBufferSubData(GL_ARRAY_BUFFER, subBufferOffset,
                      obj.VertexCount() * elementSize, obj.GetVertices());
      CheckOpenGLError();

      // index, sizeof of element, type, normalized, stride, start of data
      glEnableVertexAttribArray(vertexAttrPtr);
      glVertexAttribPointer(vertexAttrPtr, 3, GL_FLOAT, GL_FALSE, elementSize,
                            (uint8_t *)0 + subBufferOffset);
      CheckOpenGLError();

      subBufferOffset += elementSize * obj.VertexCount();

      // Color
      if (obj.ColorCount() == 1) {
        glDisableVertexAttribArray(colorAttrPtr);
        Color color = obj.GetColors()[0];
        glVertexAttrib4f(colorAttrPtr, color.Red, color.Green, color.Blue,
                         color.Alpha);
        CheckOpenGLError();
      } else if (obj.ColorCount() == obj.VertexCount()) {
        elementSize = sizeof(Color);
        // Copy over color
        // Target type, first index, how many (bytes), data
        glBufferSubData(GL_VERTEX_ARRAY, subBufferOffset,
                        obj.ColorCount() * elementSize, obj.GetColors());
        CheckOpenGLError();

        // Enable color attribute
        // index, sizeof of element, type, normalized, stride, start of data
        glEnableVertexAttribArray(colorAttrPtr);
        glVertexAttribPointer(colorAttrPtr, 3, GL_FLOAT, GL_FALSE, elementSize,
                              (uint8_t *)0 + subBufferOffset);
        CheckOpenGLError();
        subBufferOffset += elementSize * obj.NormalCount();
      } else {
        glDisableVertexAttribArray(colorAttrPtr);
        glVertexAttrib4f(colorAttrPtr, 1, 1, 1, 1);
      }

      // Normals
      if (obj.NormalCount()) {
        elementSize = sizeof(jerobins::math::Vec3<float>);

        // Copy over normals
        // Target type, first index, how many (bytes), data
        glBufferSubData(GL_VERTEX_ARRAY, subBufferOffset,
                        obj.NormalCount() * sizeof(jerobins::math::Vec3<float>),
                        obj.GetNormals());
        CheckOpenGLError();

        // Enable normal attribute
        // index, sizeof of element, type, normalized, stride, start of data
        glEnableVertexAttribArray(normalAttrPtr);
        glVertexAttribPointer(normalAttrPtr, 3, GL_FLOAT, GL_FALSE,
                              sizeof(jerobins::math::Vec3<float>),
                              (uint8_t *)0 + subBufferOffset);

        CheckOpenGLError();
        subBufferOffset +=
            sizeof(jerobins::math::Vec3<float>) * obj.NormalCount();
      } else {
        glDisableVertexAttribArray(normalAttrPtr);
      }

      // Textures
      if (obj.TextureCount()) {
        elementSize = sizeof(jerobins::math::Vec2<int>);
        // Copy over textures
        // Target type, first index, how many (bytes), data
        glBufferSubData(GL_VERTEX_ARRAY, subBufferOffset,
                        obj.TextureCount() * elementSize,
                        obj.GetTexureCoords());

        CheckOpenGLError();

        // Enable texture attribute
        // index, sizeof of element, type, normalized, stride, start of data
        glEnableVertexAttribArray(textureAttrPtr);
        glVertexAttribPointer(textureAttrPtr, 3, GL_FLOAT, GL_FALSE,
                              elementSize, (uint8_t *)0 + subBufferOffset);
        subBufferOffset += elementSize * obj.TextureCount();
        CheckOpenGLError();

      } else {
        glDisableVertexAttribArray(textureAttrPtr);
        CheckOpenGLError();
      }

      if (obj.IndicesCount()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
                        sizeof(int) * obj.IndicesCount(), obj.GetIndices());
        CheckOpenGLError();
      }

      GLuint type = RenderTypeToGLType(obj.Type());
      if (type != GL_INVALID_ENUM) {
        if (obj.IndicesCount()) {
          glDrawElements(type, obj.VertexCount(), GL_UNSIGNED_INT, 0);
        } else {
          glDrawArrays(type, 0, obj.VertexCount());
        }
      }
      CheckOpenGLError();

      glBindVertexArray(0);
      CheckOpenGLError();

      obj.Program().Detach();
      CheckOpenGLError();
    }
  } // namespace render
} // namespace jerobins