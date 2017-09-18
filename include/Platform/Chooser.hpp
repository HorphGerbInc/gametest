
#ifndef _CHOOSER_HPP_
#define _CHOOSER_HPP_

#ifdef __linux__
#include <Platform/X11/X11Window.hpp>
#elif _WIN32
#include <Platform/Windows/WindowsWindow.hpp>
#elif __APPLE__
#include <Platform/OSX/OSXWindow.hpp>
#else
#error "Unsupported operating system."
#endif

#endif