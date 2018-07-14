
#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <string>

#include <Render/OpenGL.hpp>

namespace jerobins {
  namespace platform {

    /// Base class for windows which drawing occurs
    class Window {
    public:
      /**
       * @brief Create a new window.
       *
       * @param name        The name of the window which displays in the title
       * bar.
       * @param height      The height of the window.
       * @param width       The width of the window.
       * @param fullscreen  Specifies if fullscreen.
       * @param borderless  Specifies if borderless.
       * @param resizable   Specifies if resizable.
       * @return Window*    The new window.
       */
      static Window *Create(std::string name, int height = 720,
                            int width = 1280, bool fullscreen = false,
                            bool borderless = false, bool resizable = true);

      /**
       * @brief Returns the title of the window.
       *
       * @return std::string  The window title.
       */
      std::string GetTitle() const { return name; }

      /**
       * @brief Returns the aspect ration of the window.
       *
       * @return float  The aspect ratio.
       */
      float AspectRatio() const { return (float)width / (float)height; }

      /**
       * @brief Returns if the window is borderless or not.
       *
       * @return true   Is borderless.
       * @return false  Is not borderless.
       */
      bool IsBorderless() const { return borderless; }

      /**
       * @brief Returns if the window is fullscreen or not.
       *
       * @return true   Is fullscreen.
       * @return false  Is not full screen.
       */
      bool IsFullScreen() const { return fullscreen; }

      /**
       * @brief Returns if the window has focus.
       *
       * @return true   Has focus.
       * @return false  Does not have focus.
       */
      bool HasFocus() const { return hasFocus; }

      /**
       * @brief Returns if resizable.
       *
       * @return true   Resizable.
       * @return false  Not resizable.
       */
      bool Resizable() const { return !fullscreen && resizable; }

      /**
       * @brief Returns the window's height.
       *
       * @return int Height.
       */
      int Height() const { return height; }

      /**
       * @brief Returns the window's width.
       *
       * @return int Width.
       */
      int Width() const { return width; }

      /**
       * @brief Get the windows X position.
       *
       * @return int X position.
       */
      int GetX() const { return x; }

      /**
       * @brief Get the windows Y position.
       *
       * @return int Y position.
       */
      int GetY() const { return y; }

      // Returns true if window is visible, false otherwise.
      bool IsVisible() const { return visible; }

      /**
       * @brief Sets the windows borderless state.
       *
       * @param isBorderless  New state.
       */
      virtual void Borderless(bool isBorderless) = 0;

      /**
       * @brief Sets the windows fullscreen state.
       *
       * @param isFullScreen New state.
       */
      virtual void FullScreen(bool isFullScreen) = 0;

      /**
       * @brief Returns true if the window has mouse focus, false otherwise.
       *
       * @return true   Has focus.
       * @return false  Does not have focus.
       */
      virtual bool HasMouseFocus() const = 0;

      /**
       * @brief Hides the windows.
       *
       */
      virtual void Hide() = 0;

      /**
       * @brief Shows the window.
       *
       */
      virtual void Show() = 0;

      /**
       * @brief Repaints the windows.
       *
       */
      virtual void Repaint() = 0;

      /**
       * @brief Sets the X position of the top left of the window.
       *
       * @param x New X position.
       */
      virtual void SetX(int x) = 0;

      /**
       * @brief Sets the Y position of the top left of the window.
       *
       * @param y New Y position.
       */
      virtual void SetY(int y) = 0;

      /**
       * @brief Set the window's height.
       *
       * @param height New height.
       */
      virtual void SetHeight(int height) = 0;

      /**
       * @brief Set the window's width.
       *
       * @param width New width.
       */
      virtual void SetWidth(int width) = 0;

      /**
       * @brief Set the position of the top left corner of the window.
       *
       * @param x New X.
       * @param y New Y.
       */
      virtual void SetPosition(int x, int y) = 0;

      /**
       * @brief Set the size of the window.
       *
       * @param height New height.
       * @param width New widht.
       */
      virtual void SetSize(int height, int width) = 0;

      /**
       * @brief Set the height and position of the window.
       *
       * @param x       New X position.
       * @param y       New Y position.
       * @param height  New height.
       * @param width   New width.
       */
      virtual void SetGeometry(int x, int y, int height, int width) = 0;

      /**
       * @brief Handle all pending events.
       *
       */
      virtual void HandleEvents() = 0;

      /**
       * @brief Create and bind to a context.
       *
       */
      virtual void BindContext() = 0;

      /**
       * @brief Unbind and release the context.
       *
       */
      virtual void ReleaseContext() = 0;

      /**
       * @brief Swap buffers.
       *
       */
      virtual void SwapBuffer() = 0;

    protected:
      // Set all the parameters.
      Window(std::string name, int height, int width, bool fullscreen,
             bool borderless, bool resizable);

      bool fullscreen, borderless;
      bool resizable;
      bool hasFocus;
      bool visible;
      std::string name;
      int x, y, height, width;
    };
  } // namespace platform
} // namespace jerobins

#endif