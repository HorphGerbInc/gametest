
#include <catch.hpp>

#include <Platform/Windows/WindowsWindow.hpp>

const int Milliseconds = 1;
const int Seconds = 1000 * Milliseconds;
const int Minutes = 60 * Seconds;
const int Hours = 60 * Minutes;
const int Days = 24 * Hours;

TEST_CASE("WindowsWindow", "Create object") {
  int height = 800;
  int width = height * 16 / 10;
  jerobins::platform::WindowsWindow window(nullptr, "test", height, width);

  REQUIRE(window.Height() == height);
  REQUIRE(window.Width() == width);
  REQUIRE(window.IsFullScreen() == false);
  REQUIRE(window.IsBorderless() == false);

  window.Show();

  REQUIRE(window.Height() == height);
  REQUIRE(window.Width() == width);
  REQUIRE(window.IsFullScreen() == false);
  REQUIRE(window.IsBorderless() == false);

  SYSTEMTIME time;
  GetSystemTime(&time);
  LONG start = (time.wSecond * 1000) + time.wMilliseconds;
  LONG end = start + 5 * Seconds;
  while (start < end) {
    window.HandleEvents();
    GetSystemTime(&time);
    start = (time.wSecond * 1000) + time.wMilliseconds;
  }
}
