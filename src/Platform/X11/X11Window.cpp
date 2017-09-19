
#include <iostream>
#include <stdexcept>

#include <Platform/X11/X11Window.hpp>

namespace jerobins {
  namespace platform {

    X11Window::X11Window(std::string name, int height, int width,
                         bool fullscreen, bool borderless, bool resizable)
        : Window(name, height, width, fullscreen, borderless, resizable) {

      this->display = XOpenDisplay(NULL);
      if (this->display == NULL) {
        throw std::runtime_error("Could not create display.");
      }
      
      this->screen = DefaultScreenOfDisplay(this->display);

      int sWidth = WidthOfScreen(this->screen);
      int sHeight = HeightOfScreen(this->screen);
      
      if(height > sHeight) height = sHeight;
      if(width > sWidth) width = sWidth;

      this->x = sWidth / 2 - width / 2;
      this->y = sHeight / 2 - height / 2;


      X11Wrapper::X11Window root = RootWindowOfScreen(this->screen);
      auto bPixel = BlackPixelOfScreen(this->screen);
      auto wPixel = WhitePixelOfScreen(this->screen);

      this->window = XCreateSimpleWindow(this->display, root, x, y, width,
                                         height, 1, bPixel, wPixel);

      XSelectInput(this->display, this->window, ExposureMask | KeyPressMask);
      XMapWindow(this->display, this->window);

      // I think everyone probably does this
      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    X11Window::~X11Window() {
      if (this->display != NULL) {
        XCloseDisplay(this->display);
      }
    }

    void X11Window::SetX(int x) { SetPosition(x, GetY()); }

    void X11Window::SetY(int y) { SetPosition(GetX(), y); }

    void X11Window::SetPosition(int x, int y) {
      SetGeometry(x, y, Width(), Height());
    }

    void X11Window::Show() {}

    void X11Window::HandleEvents() {
      XEvent event;
      XNextEvent(this->display, &event);
      switch (event.type) {
      case Expose:
        auto dgc = DefaultGCOfScreen(this->screen);
        XFillRectangle(this->display, this->window, dgc, 20, 20, 10, 10);
        break;
      }
    }

    void X11Window::Hide() {}

    void X11Window::SetHeight(int height) { SetSize(height, Width()); }

    void X11Window::SetWidth(int width) { SetSize(Height(), width); }

    void X11Window::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    bool X11Window::HasMouseFocus() const { return true; }

    void X11Window::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      if (!Resizable()) {
        height = Height();
        width = Width();
      }
    }

    void X11Window::Repaint() {}

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
      if (border == borderless) {
        return;
      }
    }
  }
}