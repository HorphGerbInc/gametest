
#ifdef __linux__

#include <functional>
#include <stdexcept>

#include <X11/X.h>
#include <X11/Xutil.h>

#include <Platform/X11/X11Window.hpp>

static Atom wm_delete_window;

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev) {
  ctxErrorOccurred = true;
  return 0;
}

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

      if (height > sHeight)
        height = sHeight;
      if (width > sWidth)
        width = sWidth;

      this->x = sWidth / 2 - width / 2;
      this->y = sHeight / 2 - height / 2;

      X11Wrapper::X11Window root = RootWindowOfScreen(this->screen);
      auto bPixel = BlackPixelOfScreen(this->screen);
      auto wPixel = WhitePixelOfScreen(this->screen);

      XSizeHints my_hints = {0};

      my_hints.flags = PPosition | PSize;
      my_hints.x = x;
      my_hints.y = y;
      my_hints.width = width;
      my_hints.height = height;

      this->window = XCreateSimpleWindow(this->display, root, x, y, height,
                                         width, 1, bPixel, wPixel);

      XSetNormalHints(this->display, this->window, &my_hints);

      XSelectInput(this->display, this->window, ExposureMask | KeyPressMask);

      wm_delete_window = XInternAtom(this->display, "WM_DELETE_WINDOW", False);
      XSetWMProtocols(this->display, this->window, &wm_delete_window, 1);

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
      if (XMoveWindow(this->display, this->window, x, y) == 0) {
        this->x = x;
        this->y = y;
      }
    }

    typedef int(FunctionPtr)(Display *, XEvent *, XPointer);

    template <int T>
    Bool Checker(X11Wrapper::X11Display *disp, XEvent *event, XPointer arg) {
      return event->type == T;
    };

    void X11Window::Show() {
      XMapWindow(this->display, this->window);
      this->visible = true;
    }

    void X11Window::HandleEvents() {

      XEvent event;
      XConfigureEvent *xc;
      
      while (XPending(this->display)) {
        XNextEvent(display, &event);
        switch (event.type) {
          {
          case ClientMessage:
            if ((Atom)event.xclient.data.l[0] == wm_delete_window) {
              this->visible = false;
            }
            break;
            case ConfigureNotify:
            xc = &(event.xconfigure);
            this->width = xc->width;
            this->height = xc->height;
            break;            
          }
        }
      }
    }

    void X11Window::Hide() {
      XUnmapWindow(this->display, this->window);
      this->visible = false;
    }

    void X11Window::SetHeight(int height) { SetSize(height, Width()); }

    void X11Window::SetWidth(int width) { SetSize(Height(), width); }

    void X11Window::SetSize(int height, int width) {

      if (!Resizable()) {
        height = Height();
        width = Width();
      }

      if (XResizeWindow(this->display, this->window, width, height) == 0) {
        this->height = height;
        this->width = width;
      }
    }

    bool X11Window::HasMouseFocus() const { return true; }

    void X11Window::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      SetSize(height, width);
      SetPosition(x, y);

      Repaint();
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

    static GLint defaultAttributes[] = {GLX_RGBA,
                                        GLX_DEPTH_SIZE,
                                        24,
                                        GLX_DOUBLEBUFFER,
                                        GLX_CONTEXT_MAJOR_VERSION_ARB,
                                        3,
                                        GLX_CONTEXT_MINOR_VERSION_ARB,
                                        0,
                                        None};

    void X11Window::BindOpenGL(GLint *glAttributes) {

      if (glAttributes == NULL) {
        glAttributes = defaultAttributes;
      }

      if (glContext != NULL) {
        UnbindOpenGL();
      }

      XSync(display, False);

      XVisualInfo *vi = glXChooseVisual(
          this->display, XScreenNumberOfScreen(this->screen), glAttributes);
      glContext = glXCreateContext(this->display, vi, NULL, GL_TRUE);
      glXMakeCurrent(this->display, this->window, glContext);
    }

    void X11Window::UnbindOpenGL() {
      if (this->glContext) {
        glXMakeCurrent(this->display, 0, 0);
        glXDestroyContext(this->display, this->glContext);
        this->glContext = NULL;
      }
    }

    void X11Window::Borderless(bool border) {
      if (border == borderless) {
        return;
      }
    }

    void X11Window::SwapBuffer() {
      glXSwapBuffers(this->display, this->window);
    }
  }
}

#endif