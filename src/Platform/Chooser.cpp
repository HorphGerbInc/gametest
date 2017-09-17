
#ifdef __linux__
#include "X11/X11Window.cpp"
#elif _WIN32
#include "Windows/WindowsWindow.cpp"
#elif __APPLE__
#include "OSX/OSXWindow.cpp"
#else
#error "Unsupported operating system."
#endif
