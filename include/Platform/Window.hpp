
#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <string>

namespace jerobins {
  namespace platform {

    /// Base class for windows which drawing occurs
    class Window {
    public:
      // Set all the parameters.
      Window(std::string name, int height, int width, bool fullscreen,
             bool borderless, bool resizable) {
        this->height = height;
        this->width = width;
        this->fullscreen = fullscreen;
        this->borderless = borderless;
      }

      // Return title of window.
      std::string GetTitle() const { return name; }

      // AspectRatio of the window.
      float AspectRatio() const { return (float)width / (float)height; }

      // Returns true if borderless window, false otherwise.
      bool BorderLess() const { return borderless; }

      // Returns true if fullscreen window, false otherwise.
      bool FullScreen() const { return fullscreen; }

      // Returns true if the window has focus
      bool HasFocus() const { return hasFocus; }

      // Returns true if window can be resized, false otherwise.
      bool Resizable() const { return !fullscreen && resizable; }

      // returns the height of the window.
      int Height() const { return height; }

      // returns the width of the window.
      int Width() const { return width; }

      // returns the x position of the top left corner of the window.
      int GetX() const { return x; }

      // returns the y position of the top left corner of the window.
      int GetY() const { return y;}

      // Enables or disables borderless
      virtual void Borderless(bool isBorderless) = 0;

      // Enables or disables fullscreen
      virtual void FullScreen(bool isFullScreen) = 0;

      // Returns true if the mouse is located within the window.
      virtual bool HasMouseFocus() const = 0;

      // Hide the window.
      virtual void Hide() = 0;

      // Show the window.
      virtual void Show() = 0;

      // Repaint the window.
      virtual void Repaint() = 0;

      // Set the position of the left of the window.
      virtual void SetX(int x) = 0;

      // Set the position of the top of the window.
      virtual void SetY(int y) = 0;

      // Set the height of the window.
      virtual void SetHeight(int height) = 0;

      // Set the width of th window.
      virtual void SetWidth(int width) = 0;

      // Set the position of the top left of the window.
      virtual void SetPosition(int x, int y) = 0;

      // Set the size of the window.
      virtual void SetSize(int height, int width) = 0;

      // Set the position and size of the window.
      virtual void SetGeometry(int x, int y, int height, int width) = 0;

    protected:
      bool fullscreen, borderless;
      bool resizable;
      bool hasFocus;
      std::string name;
      int x, y, height, width;
    };
  }
}

#endif