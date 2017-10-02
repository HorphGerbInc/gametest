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

namespace jerobins {
  namespace render {
    namespace opengl {
      void CheckError();
    }
  }
}

#endif
