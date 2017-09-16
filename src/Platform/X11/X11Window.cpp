
#include <Platform/X11/X11Window.hpp>

namespace jerobins {
  namespace platform {

    void X11Window::X11Window(std::string name, int height, int width,
                              bool fullscreen, bool borderless)
        : Window(name, height, width, fullscreen, borderless, bool resizable) {

      // I think everyone probably does this
      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    void X11Window::SetX(int x) { SetPosition(x, GetY()); }

    void X11Window::SetY(int y) { SetPosition(GetX(), y); }

    void X11Window::SetPosition(int x, int y) {
      SetGeometry(x, y, GetWidth(), GetHeight());
    }

    void X11Window::Show() { ShowWindow(hwnd, SW_SHOW); }

    void X11Window::Hide() { ShowWindow(hwnd, SW_HIDE); }

    void X11Window::SetHeight(int height) { SetSize(height, GetWidth()); }

    void X11Window::SetWidth(int width) { SetSize(GetHeight(), width); }

    void X11Window::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    void X11Window::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      if (!Resizable()) {
        height = GetHeight();
        width = GetWidth();
      }

      if (OS_DEPENDENT_CALL(x, y, width, height)) {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;
      }
    }

    void X11Window::Repaint() {
      OS_DEPENDENT_CALL();      
    }

    void X11Window::FullScreen(bool setFullScreen) {
      // nothing to do
      if (this->fullscreen == setFullScreen)
        return;

      if (setFullScreen) {
        OS_DEPENDENT_CALL();
      } else if (Resizable()) {
        OS_DEPENDENT_CALL();
        Repaint();
      } else {
        OS_DEPENDENT_CALL();
        Repaint();
      }
    }
  }
}