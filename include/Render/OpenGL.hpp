/*
 *  This includes the opengl headers and sets up everything
 */
#ifndef _OPENGL_HPP_
#define _OPENGL_HPP_

#define GL_GLEXT_PROTOTYPES 1

#ifdef __linux__
#include <glad/glad.h>
#else
#include <glad/glad.h>
#endif

#define _F __FILE__
#define _L __LINE__

#define CheckOpenGLError_0_ARG() CheckOpenGLError_2_ARG(_F, _L)
#define CheckOpenGLError_1_ARG(_F_) CheckOpenGLError_2_ARG(_F_, _L)

#define CheckOpenGLError_2_ARG(_F_, _L_)                                        \
  jerobins::render::opengl::CheckError(__FILE__, _L_)

// Return the 3rd argument.
#define _3RD(arg1, arg2, arg3, ...) arg3

#define CheckOpenGLChooser(...)                                                 \
  _3RD(__VA_ARGS__, CheckOpenGLError_2_ARG, CheckOpenGLError_1_ARG,             \
       CheckOpenGLError_0_ARG, )

#define CheckOpenGLError(...) CheckOpenGLChooser(__VA_ARGS__)(__VA_ARGS__)

#define CheckGL(OP)                                                             \
do {                                                                            \
    int MACRO_L = _L;                                                           \
    OP;                                                                         \
    CheckOpenGLError(_F, MACRO_L);                                              \
} while (0)

namespace jerobins {
  namespace render {
    namespace opengl {
      /**
       * @brief Check to see if there is an error in OpenGL.
       * 
       * @detailed Check to see if an OpenGL error occurred.  If so we 
       * log it along with the file and line in which is occurrs.
       * 
       * @param file File where error occurred.
       * @param line Line where error occurred.
       */
      void CheckError(const char *file, int line);
    }
  } // namespace render
} // namespace jerobins

#endif
