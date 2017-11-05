
#include <Common/Logger.hpp>
#include <Render/OpenGL.hpp>

namespace jerobins {
  namespace render {
    namespace opengl {

      void CheckError(const char* filename, int line) {
        std::string file(filename);
        switch (glGetError()) {
        case GL_NO_ERROR:
          break;
        case GL_INVALID_ENUM:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Invalid Enum",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        case GL_INVALID_VALUE:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Invalid value.",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        case GL_INVALID_OPERATION:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Invalid operation.",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Invalid framebuffer operation.",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        case GL_OUT_OF_MEMORY:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Out of memory.",
              jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        default:
          jerobins::common::Logger::GetLogger()->Log(file, line,
              "OpenGl Error: Unkown.", jerobins::common::LoggingLevel::Error);
          exit(1);
          break;
        }
      }
    }
  }
}