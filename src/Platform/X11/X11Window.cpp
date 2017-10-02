
#ifdef __linux__

#include <functional>
#include <iostream>
#include <stdexcept>

#include <X11/X.h>
#include <X11/Xutil.h>

// This should include everything needed for using glx functions
// BROKEN

#include <Common/ArgumentCheck.hpp>
#include <Math/Operations.hpp>
#include <Platform/X11/X11Window.hpp>

static Atom wm_delete_window;

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev) {
  ctxErrorOccurred = true;
  return 0;
}

// Found this in Godot, thanks!
static GLint attributes[] = {None};
// Found this in Godot, thanks!
static GLint backup[] = {GLX_RENDER_TYPE,
                         GLX_RGBA_BIT,
                         GLX_DRAWABLE_TYPE,
                         GLX_WINDOW_BIT,
                         GLX_DOUBLEBUFFER,
                         true,
                         GLX_RED_SIZE,
                         1,
                         GLX_GREEN_SIZE,
                         1,
                         GLX_BLUE_SIZE,
                         1,
                         GLX_DEPTH_SIZE,
                         24,
                         None};

template <class T> void NullCheck(const std::string &msg, T *ptr) {
  if (ptr == NULL || ptr == nullptr) {
    throw std::runtime_error(msg);
  }
}

namespace jerobins {
  namespace platform {

    X11Window::X11Window(std::string name, int height, int width,
                         bool fullscreen, bool borderless, bool resizable)
        : Window(name, height, width, fullscreen, borderless, resizable) {

      this->display = XOpenDisplay(NULL);
      NullCheck("Could not create display.", display);

      int defaultScreen = DefaultScreen(this->display);

      this->screen = DefaultScreenOfDisplay(this->display);
      NullCheck("Could not create screen.", screen);

      // Screen dimensions
      int sWidth = WidthOfScreen(this->screen);
      int sHeight = HeightOfScreen(this->screen);

      // Clamp
      height = jerobins::math::Operations::Clamp(0, sHeight, height);
      width = jerobins::math::Operations::Clamp(0, sWidth, width);

      // Place in the middle
      this->x = sWidth / 2 - width / 2;
      this->y = sHeight / 2 - height / 2;

      NullCheck("glXChooseFBConfig is null!", glXChooseFBConfig);
      int fbcount;
      GLXFBConfig *frameBuffers =
          glXChooseFBConfig(this->display, defaultScreen, attributes, &fbcount);
      NullCheck("Could not find a framebuffer configuration", frameBuffers);

      // Just take the first framebuffer
      XVisualInfo *vi =
          glXGetVisualFromFBConfig(this->display, frameBuffers[0]);

      // Window attributes
      XSetWindowAttributes swa;

      swa.colormap =
          XCreateColormap(this->display, RootWindow(this->display, vi->screen),
                          vi->visual, AllocNone);
      swa.border_pixel = 0;
      swa.event_mask = StructureNotifyMask;

      // XCreateWindow parameters
      auto rootWindow = RootWindow(this->display, vi->screen);
      int borderWidth = (borderless) ? 0 : 1;
      unsigned long valueMask = CWBorderPixel | CWColormap | CWEventMask;

      this->window = XCreateWindow(this->display, rootWindow, x, y, width,
                                   height, borderWidth, vi->depth, InputOutput,
                                   vi->visual, valueMask, &swa);
      NullCheck("Could not create XWindow", (void *)this->window);

      XClassHint *hints;
      hints = XAllocClassHint();
      if (hints) {
        hints->res_name = (char *)"Jerobins_Engine";
        hints->res_class = (char *)"Jerobins";
      }
      XSetClassHint(this->display, this->window, hints);
      XFree(hints);

      this->glContext = glXCreateContext(this->display, vi, NULL, GL_TRUE);
      NullCheck("OpenGL Context is null", this->glContext);
          
      XSelectInput(this->display, this->window, ExposureMask | KeyPressMask);

      wm_delete_window = XInternAtom(this->display, "WM_DELETE_WINDOW", False);
      XSetWMProtocols(this->display, this->window, &wm_delete_window, 1);

      // I think everyone probably does this
      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);

      this->BindContext();
      XFree(vi);
      XFree(frameBuffers);

      // make sure everything is okay before we leave
      jerobins::common::ArgumentCheck<X11Wrapper::X11Screen>::IsNotNull(
          "screen", screen);
      jerobins::common::ArgumentCheck<X11Wrapper::X11Display>::IsNotNull(
          "display", display);
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

    void X11Window::BindContext() {
      glXMakeCurrent(this->display, this->window, glContext);
    }

    void X11Window::ReleaseContext() {
      glXMakeCurrent(this->display, None, NULL);
    }

    void X11Window::Borderless(bool border) {
      if (border == borderless) {
        return;
      }
      // TODO: enable borderless
    }

    void X11Window::SwapBuffer() {
      glXSwapBuffers(this->display, this->window);
    }
  }
}

#endif