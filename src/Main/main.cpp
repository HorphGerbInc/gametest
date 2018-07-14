
// StdLib
#include <fstream>
#include <iostream>

// Jerobins
#include <Common/CommandLineArguments.hpp>
#include <Common/Configuration.hpp>
#include <Common/Constants.hpp>
#include <Common/Logger.hpp>
#include <Common/StringUtil.hpp>
#include <Common/Timer.hpp>
#include <Platform/Window.hpp>
#include <Render/OpenGL.hpp>
#include <Render/Renderer.hpp>
#include <Resource/Model.hpp>
#include <Resource/ShaderProgram.hpp>

// Convert a frame duration to frames per seconds
float DurationToFPS(double milliseconds) {
  return (float)((1.0 * Seconds) / milliseconds);
}

// Convert frames per second to duration of single frame.
float FPSToDuration(double fps) { return (float)((1.0 * Seconds) / fps); }

// Cap the duration to a certain frames per second
void CapFramesPerSeconds(float fps, jerobins::common::Timer &timer) {
  while (timer.Duration() <= FPSToDuration(fps)) {
  }
}

// OpenGL variables
static GLuint VertexArrayID;
static GLuint vertexbuffer;

jerobins::resource::ShaderProgram program;

void cleanupOpenGL() {
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
}

jerobins::common::CommandLineArguments initCommandLine(int argc, char *argv[]) {
  jerobins::common::CommandLineArguments cli;
  cli.AddFlag("debug");
  cli.AddParameter("test");
  cli.Parse(argc, argv);
  return cli;
}

/**/
int main(int argc, char *argv[]) {
  jerobins::common::Logger::GetLogger()->Log("Starting");
  try {
    // Handle command line arguemnts
    jerobins::common::CommandLineArguments cli = initCommandLine(argc, argv);

    jerobins::platform::Window *window =
        jerobins::platform::Window::Create("main");

    window->Show();
    window->BindContext();

    jerobins::render::Renderer renderer;
    renderer.Init();
    CheckOpenGLError();

    auto triangle = jerobins::resource::Model::Load("models/red_triangle.json");

    while (window->IsVisible()) {

      jerobins::common::Timer timer;
      timer.Start();
      window->HandleEvents();
      CheckOpenGLError();

      renderer.Render(triangle);
      CheckOpenGLError();

      window->SwapBuffer();

      CapFramesPerSeconds(64, timer);
      timer.Stop();
      jerobins::common::Logger::GetLogger()->Log(
          jerobins::common::StringUtil::Format(
              "FPS: %f", DurationToFPS((double)timer.Duration())));
    }
    cleanupOpenGL();

    window->ReleaseContext();
    window->Hide();
    delete window;

  } catch (std::runtime_error &e) {
    std::cout << std::string(e.what()) << std::endl;
  }

  return EXIT_SUCCESS;
}