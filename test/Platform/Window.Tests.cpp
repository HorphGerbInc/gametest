
// StdLib
#include <iostream>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Common/Timer.hpp>
#include <Platform/Window.hpp>

TEST_CASE("WindowsWindow", "Create object") {
  int height = 800;
  int width = height * 16 / 10;

  jerobins::platform::Window * ptrWindow = jerobins::platform::Window::Create("test", height, width);
  jerobins::platform::Window& window = *ptrWindow;

  REQUIRE(window.Height() == height);
  REQUIRE(window.Width() == width);
  REQUIRE(window.IsFullScreen() == false);
  REQUIRE(window.IsBorderless() == false);

  window.Show();

  REQUIRE(window.Height() == height);
  REQUIRE(window.Width() == width);
  REQUIRE(window.IsFullScreen() == false);
  REQUIRE(window.IsBorderless() == false);

  jerobins::common::Timer timer;
  timer.Start();
  while (timer.Duration() < 2 * Seconds) {
    window.HandleEvents();
  }
  timer.Stop();

  delete ptrWindow;
}
