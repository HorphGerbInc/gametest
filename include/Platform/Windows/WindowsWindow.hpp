
#ifndef UNICODE
#define UNICODE
#endif

#include <Platform/Window.hpp>

#include <windows.h>

#include <string>

namespace jerobins {
  namespace platform {
    class WindowsWindow : public Window {

    public:
      WindowsWindow(HINSTANCE instance, const std::string name,
                    int height = 1080, int width = 1920,
                    bool fullscreen = false, bool borderless = false,
                    bool resizable = true);

      // Enables or disables borderless
      virtual void Borderless(bool isBorderless);

      // Enables or disables fullscreen
      virtual void FullScreen(bool isFullScreen);

      // Handle window events.
      virtual void HandleEvents();

      // Returns true if window has mouse focus.
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

    private:
      HWND windowHandle;
    };
  }
}