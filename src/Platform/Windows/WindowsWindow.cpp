
#ifdef _WIN32

// StdLib
#include <iostream>

// Jerobins
#include <Platform/Windows/WindowsWindow.hpp>

struct Point2D {
  int x, y;
};

// Get main monitor handle
HMONITOR GetPrimaryMonitorHandle() {
  const POINT ptZero = {0, 0};
  return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
}

Point2D GetScreenSize() { return {}; }

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

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {

	jerobins::platform::WindowsWindow* me = (jerobins::platform::WindowsWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (me) return me->WindowsProc(hwnd, uMsg, wParam, lParam);
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace jerobins {
  namespace platform {

    WindowsWindow::WindowsWindow(HINSTANCE hInstance, std::string name,
                                 int height, int width, bool fullscreen,
                                 bool borderless, bool resizable)
        : Window(name, height, width, fullscreen, borderless, resizable) {

      int w = GetSystemMetrics(SM_CXSCREEN);
      int h = GetSystemMetrics(SM_CYSCREEN);

      if (width > w)
        width = w;
      if (height > h)
        height = h;

      x = w / 2;
      y = h / 2;

      x -= width / 2;
      y -= height / 2;

      // Register the window class.
      wchar_t ClassName[1025] = {0};
      int result = MultiByteToWideChar(CP_UTF8, 0, name.c_str(),
                                       (int)name.length(), ClassName, 1024);
      ClassName[1024] = 0;

      if (result == 0) {
        throw std::runtime_error("could not convert to wide character: " +
                                 GetLastErrorAsString());
      }

      WNDCLASS wc = {0};

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
                                     x, y, width, height,

                                     NULL,      // Parent window
                                     NULL,      // Menu
                                     hInstance, // Instance handle
                                     NULL       // Additional application data
                                     );

      if (windowHandle == NULL) {
        std::string msg = GetLastErrorAsString();
        throw std::runtime_error("Could not create the window: " + msg);
      }

	  SetWindowLongPtr(this->windowHandle, GWLP_USERDATA, (LONG_PTR)this);


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
      this->visible = true;
    }

    void WindowsWindow::HandleEvents() {
      MSG msg;
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    bool WindowsWindow::HasMouseFocus() const { return true; }

	void WindowsWindow::Hide() { ShowWindow(windowHandle, SW_HIDE); this->visible = false; }

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

    // Create the OpenGL context
    void WindowsWindow::BindOpenGL(GLint *glAttributes) {

      if (this->context) {
        return;
      }

      static PIXELFORMATDESCRIPTOR pfd = {0};
      pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
      pfd.nVersion = 1;
      pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pfd.iPixelType = PFD_TYPE_RGBA;
      pfd.cColorBits = 24;
      pfd.cDepthBits = 24;
      pfd.iLayerType = PFD_MAIN_PLANE;

      if (!(hardwareDescriptor = GetDC(windowHandle))) {
        MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR",
                   MB_OK | MB_ICONEXCLAMATION);
        return; // Return FALSE
      }

      if (!(this->pixel_format = ChoosePixelFormat(
                hardwareDescriptor,
                &pfd))) // Did Windows Find A Matching Pixel Format?
      {
        MessageBox(NULL, L"Can't Find A Suitable pixel_format.", L"ERROR",
                   MB_OK | MB_ICONEXCLAMATION);
        return; // Return FALSE
      }

      if (!SetPixelFormat(hardwareDescriptor, pixel_format,
                          &pfd)) // Are We Able To Set The Pixel Format?
      {
        MessageBox(NULL, L"Can't Set The pixel_format.", L"ERROR",
                   MB_OK | MB_ICONEXCLAMATION);
        return; // Return FALSE
      }

      if (!(context = wglCreateContext(
                hardwareDescriptor))) // Are We Able To Get A Rendering Context?
      {
        MessageBox(NULL, L"Can't Create A Temporary GL Rendering Context.",
                   L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return; // Return FALSE
      }

      wglMakeCurrent(hardwareDescriptor, context);
    }

    // Remove the OpenGL context
    void WindowsWindow::UnbindOpenGL() {
      if (this->context) {
        wglDeleteContext(this->context);
        this->context = NULL;
      }
    }

    // Swap the buffers
    void WindowsWindow::SwapBuffer() { SwapBuffers(this->hardwareDescriptor); }

	LRESULT CALLBACK WindowsWindow::WindowsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			std::cout << "Destroy" << std::endl;
			this->Hide();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}
  }
}

#endif