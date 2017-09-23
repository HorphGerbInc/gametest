
#include <Platform/Window.hpp>
#ifdef __linux__
#include <Platform/X11/X11Window.hpp>
#elif _WIN32
#include <Platform/Windows/WindowsWindow.hpp>
#elif __APPLE__
#include <Platform/OSX/OSXWindow.hpp>
#else
#error "Unsupported Operating System"
#endif
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
      return new jerobins::platform::X11Window(name, height, width, fullscreen, borderless,
                           resizable);
#elif _WIN32
      return new jerobins::platform::WindowsWindow(NULL, name, height, width, fullscreen, borderless,
                               resizable);
#elif __APPLE__
      return new jerobins::platform::OSXWindow(name, height, width, fullscreen, borderless,
                           resizable);
#else
#error "Unsupported operating system."
#endif
    }
  }
}
