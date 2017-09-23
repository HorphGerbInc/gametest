
#ifdef __APPLE__

#include <Platform/OXS/OSXWindow.hpp>

namespace jerobins {
  namespace platform {

    void OSXWindow::OSXWindow(std::string name, int height, int width,
                              bool fullscreen, bool borderless)
        : Window(name, height, width, fullscreen, borderless, bool resizable) {

      // I think everyone probably does this
      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    void OSXWindow::SetX(int x) { SetPosition(x, GetY()); }

    void OSXWindow::SetY(int y) { SetPosition(GetX(), y); }

    void OSXWindow::SetPosition(int x, int y) {
      SetGeometry(x, y, GetWidth(), GetHeight());
    }

    void OSXWindow::Show() { ShowWindow(hwnd, SW_SHOW); }

    void OSXWindow::Hide() { ShowWindow(hwnd, SW_HIDE); }

    void OSXWindow::SetHeight(int height) { SetSize(height, GetWidth()); }

    void OSXWindow::SetWidth(int width) { SetSize(GetHeight(), width); }

    void OSXWindow::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    void OSXWindow::SetGeometry(int x, int y, int height, int width) {
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

    void OSXWindow::Repaint() {
      OS_DEPENDENT_CALL();      
    }

    void OSXWindow::FullScreen(bool setFullScreen) {
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

#endif