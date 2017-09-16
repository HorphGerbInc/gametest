
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

    void WindowsWindow::WindowsWindow(HINSTANCE hInstance, std::string name,
                                      int height, int width, bool fullscreen,
                                      bool borderless)
        : Window(name, height, width, fullscreen, borderless, bool resizable) {

      // Register the window class.
      const wchar_t ClassName[1025] = {0};
      int result = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, name.c_str(),
                                       name.length(), ClassName, 1024);
      ClassName[1024] = 0;

      if (result != 0) {
        throw std::runtime_error(GetLastErrorAsString());
      }

      WNDCLASS wc = {};

      wc.lpfnWndProc = WindowProc;
      wc.hInstance = hInstance;
      wc.lpszClassName = ClassName;

      RegisterClass(&wc);

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
                                     CW_USEDEFAULT, CW_USEDEFAULT,
                                     CW_USEDEFAULT, CW_USEDEFAULT,

                                     NULL,      // Parent window
                                     NULL,      // Menu
                                     hInstance, // Instance handle
                                     NULL       // Additional application data
                                     );

      if (hwnd == NULL) {
        throw std::runtime_error("Could not create the window.");
      }

      SetGeometry(x, y, height, width);
      FullScreen(fullscreen);
      Borderless(borderless);
    }

    void WindowsWindow::SetX(int x) { SetPosition(x, GetY()); }

    void WindowsWindow::SetY(int y) { SetPosition(GetX(), y); }

    void WindowsWindow::SetPosition(int x, int y) {
      SetGeometry(x, y, GetWidth(), GetHeight());
    }

    void WindowsWindow::Show() { ShowWindow(hwnd, SW_SHOW); }

    void WindowsWindow::Hide() { ShowWindow(hwnd, SW_HIDE); }

    void WindowsWindow::SetHeight(int height) { SetSize(height, GetWidth()); }

    void WindowsWindow::SetWidth(int width) { SetSize(GetHeight(), width); }

    void WindowsWindow::SetSize(int height, int width) {
      SetGeometry(GetX(), GetY(), height, width);
    }

    void WindowsWindow::SetGeometry(int x, int y, int height, int width) {
      // Just don't do it
      if (!Resizable()) {
        height = GetHeight();
        width = GetWidth();
      }

      if (SetWindowPos(this->hWnd, x, y, width, height)) {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;
      }
    }

    void WindowsWindow::Repaint() {
      RECT rect;
      GetWindowRect(hWnd, &rect);
      MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, TRUE);
    }

    void WindowsWindow::FullScreen(bool setFullScreen) {
      // nothing to do
      if (this->fullscreen == setFullScreen)
        return;

      if (setFullScreen) {
        SetWindowLongPtr(hWnd, GWL_STYLE,
                         WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN |
                             WS_CLIPSIBLINGS | WS_VISIBLE);
      } else if (Resizable()) {
        SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        Repaint();
      } else {
        SetWindowLongPtr(hWnd, GWL_STYLE,
                         WS_CAPTION | WS_MINIMIZEBOX | WS_POPUPWINDOW |
                             WS_VISIBLE);
        Repaint();
      }
    }
  }
}