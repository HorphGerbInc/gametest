
#include <Common/Logger.hpp>
#include <Render/OpenGL.hpp>

namespace jerobins {
  namespace render {
    namespace opengl {

      void CheckError(const char *file, int line) {
        switch (glGetError()) {
        case GL_NO_ERROR:
          break;
        case GL_INVALID_ENUM:
          jerobins::common::Logger::GetLogger()->Log(
              jerobins::common::LoggingLevel::Error, "(%s:%d) %s", file, line,
              "OpenGl Error: Invalid Enum");
          exit(1);
          break;
        case GL_INVALID_VALUE:
          jerobins::common::Logger::GetLogger()->Log(
              jerobins::common::LoggingLevel::Error, "(%s:%d) %s", file, line,
              "OpenGl Error: Invalid value.");
          exit(1);
          break;
        case GL_INVALID_OPERATION:
          jerobins::common::Logger::GetLogger()->Log(
              jerobins::common::LoggingLevel::Error, "(%s:%d) %s", file, line,
              "OpenGl Error: Invalid operation.");
          exit(1);
          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          jerobins::common::Logger::GetLogger()->Log(
              jerobins::common::LoggingLevel::Error, "(%s:%d) %s", file, line,
              "OpenGl Error: Invalid framebuffer operation.");
          exit(1);
          break;
        case GL_OUT_OF_MEMORY:
          jerobins::common::Logger::GetLogger()->Log(
              jerobins::common::LoggingLevel::Error, "(%s:%d) %s", file, line,
              "OpenGl Error: Out of memory.");
          exit(1);
          break;
        default:
          jerobins::common::Logger::GetLogger()->Log(
              file, line, "OpenGl Error: Unkown.",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        }
      }
    } // namespace opengl
  }   // namespace render
} // namespace jerobins