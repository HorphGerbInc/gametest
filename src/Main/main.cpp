
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

void setupOpenGL() {

  program =
      jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");
  program.Link();

  // black background
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glGenVertexArrays(1, &VertexArrayID);

  glBindVertexArray(VertexArrayID);

  static const GLfloat g_vertex_buffer_data[] = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

}

void drawOpenGL() {
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  jerobins::common::Logger::GetLogger()->Log("glClear");
  jerobins::render::opengl::CheckError();

  program.Attach();
  jerobins::common::Logger::GetLogger()->Log("attach");
  jerobins::render::opengl::CheckError();

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                           // must match the layout in the shader.
                        3, // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
  glDisableVertexAttribArray(0);
}

void cleanupOpenGL() {
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
}

/**/
int main(int argc, char *argv[]) {
  jerobins::common::Logger::GetLogger()->Log("Starting");
  try {
    // Handle command line arguemnts
    jerobins::common::CommandLineArguments cli;
    cli.AddFlag("debug");
    cli.AddParameter("test");
    cli.Parse(argc, argv);

    jerobins::platform::Window *window =
        jerobins::platform::Window::Create("main");

    window->Show();
    window->BindContext();

    jerobins::render::Renderer renderer;
    renderer.Init();
    jerobins::common::Logger::GetLogger()->Log("after window init");
    jerobins::render::opengl::CheckError();

    //setupOpenGL();

    auto triangle = jerobins::resource::Model::Load("models/red_triangle.json");

    while (window->IsVisible()) {

      jerobins::common::Timer timer;
      timer.Start();
      window->HandleEvents();

      renderer.Render(triangle);
      //drawOpenGL();
      jerobins::common::Logger::GetLogger()->Log("After Render call");
      jerobins::render::opengl::CheckError();

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