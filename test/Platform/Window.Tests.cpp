
#include <catch.hpp>

#include <Platform/Windows/WindowsWindow.hpp>

TEST_CASE("WindowsWindow", "Create object")
{
    jerobins::platform::WindowsWindow window(nullptr, "test");
    window.Show();

    for(int i = 0 ; i < 5; ++i) {
        Sleep(1000);
    }
}
