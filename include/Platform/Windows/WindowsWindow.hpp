
#ifndef UNICODE
#define UNICODE
#endif

#include <Platform/Window.hpp>

#include <windows.h>

namespace jerobins {
  namespace platform {
    class WindowsWindow : public Window {

    public:
      WindowsWindow(const std::string name, int height = 1080, int width = 1920,
                    bool fullscreen = false, bool windowless = false, bool resizable = true);

      // Enables or disables borderless
      virtual void Borderless(bool isBorderless) = 0;

      // Enables or disables fullscreen
      virtual void FullScreen(bool isFullScreen) = 0;

      // Hide the window.
      virtual void Hide() = 0;

      // Show the window.
      virtual void Show() = 0;

      // Repaint the window.
      virtual void Repaint() = 0;

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

    private:
      HWnd windowHandle;
    }
  }
}