
#include <Platform/Window.hpp>

#include <Platform/Chooser.hpp>

namespace jerobins {
  namespace platform {

    Window::Window(std::string name, int height, int width, bool fullscreen,
                   bool borderless, bool resizable) {
      this->name = name;
      this->height = height;
      this->width = width;
      this->fullscreen = fullscreen;
      this->borderless = borderless;
      this->visible = false;
    }

    Window *Window::Create(std::string name, int height, int width,
                           bool fullscreen, bool borderless, bool resizable) {

#ifdef __linux__
      return new X11Window(name, height, width, fullscreen, borderless,
                           resizable);
#elif _WIN32
      return new WindowsWindow(name, height, width, fullscreen, borderless,
                               resizable);
#elif __APPLE__
      return new OSXWindow(name, height, width, fullscreen, borderless,
                           resizable);
#else
#error "Unsupported operating system."
#endif
    }
  }
}
