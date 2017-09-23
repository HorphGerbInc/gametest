/*
 *  This includes the opengl headers and sets up everything
 */
#ifndef _OPENGL_HPP_
#define _OPENGL_HPP_

#define GL_GLEXT_PROTOTYPES 1

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glext.h>

#ifdef _WIN32
#include <GL/wglext.h>
#endif

#endif