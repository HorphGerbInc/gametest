// Main entry point for common tests.

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <Platform/Window.hpp>
#include <Render/OpenGL.hpp>

int main(int argc, char *argv[]) {
  int height = 800;
  int width = height * 16 / 10;
  jerobins::platform::Window *ptrWindow =
      jerobins::platform::Window::Create("test", height, width);

  if (!gladLoadGL()) {
    std::cout << "could not load opengl" << std::endl;
    exit(-1);
  }

  int result = Catch::Session().run(argc, argv);

  return (result < 0xff ? result : 0xff);
}