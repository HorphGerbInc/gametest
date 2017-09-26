/*
 *  This includes the opengl headers and sets up everything
 */
#ifndef _OPENGL_HPP_
#define _OPENGL_HPP_

#define GL_GLEXT_PROTOTYPES 1

#ifdef __linux__
#include <glad/glad_glx.h>
#else
#include <glad/glad.h>
#endif
#endif