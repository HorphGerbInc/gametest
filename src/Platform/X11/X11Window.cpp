
#include <Platform/X11/X11Window.hpp>

namespace jerobins {
  namespace platform {

    X11Window::X11Window(std::string name, int height, int width,
                              bool fullscreen, bool borderless, bool resizable)
        : Window(name, height, width, fullscreen, borderless, resizable) {

      // I think everyone probably does this
      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    void X11Window::SetX(int x) { SetPosition(x, GetY()); }

    void X11Window::SetY(int y) { SetPosition(GetX(), y); }

    void X11Window::SetPosition(int x, int y) {
      SetGeometry(x, y, Width(), Height());
    }

    void X11Window::Show() { }

    void X11Window::HandleEvents() {
      
    }

    void X11Window::Hide() {  }

    void X11Window::SetHeight(int height) { SetSize(height, Width()); }

    void X11Window::SetWidth(int width) { SetSize(Height(), width); }

    void X11Window::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    bool X11Window::HasMouseFocus() const {
      return true;
    }

    void X11Window::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      if (!Resizable()) {
        height = Height();
        width = Width();
      }

    }

    void X11Window::Repaint() {
    }

    void X11Window::FullScreen(bool setFullScreen) {
      // nothing to do
      if (this->fullscreen == setFullScreen)
        return;

      if (setFullScreen) {
      } else if (Resizable()) {
        Repaint();
      } else {
        Repaint();
      }
    }

    void X11Window::Borderless(bool border) {
      if(border == borderless) {
        return;
      }
    }
  }
}