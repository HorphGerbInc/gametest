
#include <iostream>

#include <Platform/Windows/WindowsWindow.hpp>

std::string GetLastErrorAsString() {
  // Get the error message, if any.
  DWORD errorMessageID = ::GetLastError();
  if (errorMessageID == 0)
    return std::string(); // No error message has been recorded

  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  // Free the buffer.
  LocalFree(messageBuffer);

  return message;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace jerobins {
  namespace platform {

    WindowsWindow::WindowsWindow(HINSTANCE hInstance, std::string name,
                                 int height, int width, bool fullscreen,
                                 bool borderless, bool resizable)
        : Window(name, height, width, fullscreen, borderless, resizable) {

      HWND display = GetDesktopWindow();
	  RECT desktop;
	  GetWindowRect(display, &desktop);
	  std::cout << "Desktop size: " << desktop.right << " " << desktop.bottom << std::endl;
	  x = desktop.right / 2;
      y = desktop.bottom / 2;

      x -= width / 2;
      y -= height / 2;

	  std::cout << x << " : " << y << std::endl;
	  std::cout << width << " : " << height << std::endl;
      // Register the window class.
      wchar_t ClassName[1025] = {0};
      int result = MultiByteToWideChar(CP_UTF8, 0, name.c_str(),
                                       (int)name.length(), ClassName, 1024);
      ClassName[1024] = 0;

      if (result == 0) {
        throw std::runtime_error("could not convert to wide character: " +
                                 GetLastErrorAsString());
      }

      WNDCLASS wc = {};

      wc.lpfnWndProc = WindowProc;
      wc.hInstance = hInstance;
      wc.lpszClassName = ClassName;

      ATOM registerResult = RegisterClass(&wc);

      if (registerResult == 0) {
        throw std::runtime_error("could not register class: " +
                                 GetLastErrorAsString());
      }

      // Create the window.
      DWORD exStyle, dwStyle;
      if (borderless || fullscreen) {
        exStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
      } else {
        exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
        if (!resizable) {
          dwStyle &= ~WS_THICKFRAME;
          dwStyle &= ~WS_MAXIMIZEBOX;
        }
      }

      windowHandle = CreateWindowExW(0,         // Optional window styles.
                                     ClassName, // Window class
                                     ClassName, // Window text
                                     WS_OVERLAPPEDWINDOW, // Window style

                                     // Size and position
                                     x, y,
                                     width, height,

                                     NULL,      // Parent window
                                     NULL,      // Menu
                                     hInstance, // Instance handle
                                     NULL       // Additional application data
                                     );

      if (windowHandle == NULL) {
        std::string msg = GetLastErrorAsString();
        throw std::runtime_error("Could not create the window: " + msg);
      }

      SetSize(height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    void WindowsWindow::SetX(int x) { SetPosition(x, GetY()); }

    void WindowsWindow::SetY(int y) { SetPosition(GetX(), y); }

    void WindowsWindow::SetPosition(int x, int y) {
      SetGeometry(x, y, Width(), Height());
    }

    void WindowsWindow::Show() {
      ShowWindow(windowHandle, SW_SHOW);
      SetForegroundWindow(windowHandle);
    }

    bool WindowsWindow::HasMouseFocus() const { return true; }

    void WindowsWindow::Hide() { ShowWindow(windowHandle, SW_HIDE); }

    void WindowsWindow::SetHeight(int height) { SetSize(height, Width()); }

    void WindowsWindow::SetWidth(int width) { SetSize(Height(), width); }

    void WindowsWindow::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    void WindowsWindow::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      if (!Resizable()) {
        height = Height();
        width = Width();
      }

      if (MoveWindow(this->windowHandle, x, y, width, height, true)) {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;
      }
    }

    void WindowsWindow::Repaint() {
      RECT rect;
      GetWindowRect(windowHandle, &rect);
      MoveWindow(windowHandle, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, TRUE);
    }

    void WindowsWindow::FullScreen(bool setFullScreen) {
      // nothing to do
      if (this->fullscreen == setFullScreen)
        return;

      if (setFullScreen) {
        SetWindowLongPtr(windowHandle, GWL_STYLE,
                         WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN |
                             WS_CLIPSIBLINGS | WS_VISIBLE);
      } else if (Resizable()) {
        SetWindowLongPtr(windowHandle, GWL_STYLE,
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        Repaint();
      } else {
        SetWindowLongPtr(windowHandle, GWL_STYLE,
                         WS_CAPTION | WS_MINIMIZEBOX | WS_POPUPWINDOW |
                             WS_VISIBLE);
        Repaint();
      }
    }

    void WindowsWindow::Borderless(bool isBorderless) {
      if (this->borderless != isBorderless) {
        if (isBorderless) {

        } else {
        }
      }
    }
  }
}