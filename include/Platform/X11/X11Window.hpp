
#ifdef __linux__

#ifndef _X11WINDOW_HPP_
#define _X11WINDOW_HPP_

#include <X11/Xlib.h>

#include <Render/OpenGL.hpp>

namespace X11Wrapper {
  typedef Screen X11Screen;
  typedef Window X11Window;
  typedef Display X11Display;
};
#include <Platform/Window.hpp>

#include <GL/glx.h>

// X11 includes?

namespace jerobins {
  namespace platform {

    class X11Window : public jerobins::platform::Window {

    public:
      X11Window(const std::string name, int height = 1080, int width = 1920,
                bool fullscreen = false, bool borderless = false,
                bool resizable = true);

      ~X11Window();

      // Enables or disables borderless
      virtual void Borderless(bool isBorderless);

      virtual void HandleEvents();

      virtual bool HasMouseFocus() const;

      // Hide the window.
      virtual void Hide();

      // Show the window.
      virtual void Show();

      // Repaint the window.
      virtual void Repaint();

      // Set the position of the left of the window.
      virtual void SetX(int x);

      // Set the position of the top of the window.
      virtual void SetY(int y);

      // Set the height of the window.
      virtual void SetHeight(int height);

      // Set the width of th window.
      virtual void SetWidth(int width);

      // Set the position of the top left of the window.
      virtual void SetPosition(int x, int y);

      // Set the size of the window.
      virtual void SetSize(int height, int width);

      // Set the position and size of the window.
      virtual void SetGeometry(int x, int y, int height, int width);

      // Enables or disables fullscreen
      virtual void FullScreen(bool fullscreen);

      virtual void BindContext();

      virtual void ReleaseContext();

      virtual void SwapBuffer();
      

    private:
      // X11 dependent code
      X11Wrapper::X11Screen *screen;
      X11Wrapper::X11Display *display;
      X11Wrapper::X11Window window;
      GLXContext glContext = 0;      
    };
  }
}

// header guard
#endif

// if linux
#endif