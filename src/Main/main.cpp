
#include <iostream>

#include <Common/CommandLineArguments.hpp>
#include <Common/Configuration.hpp>
#include <Common/Constants.hpp>
#include <Common/Timer.hpp>

#include <Platform/Window.hpp>

/**/
int main(int argc, char *argv[]) {

  try {
    // Handle command line arguemnts
    jerobins::common::CommandLineArguments cli;
    cli.AddFlag("debug");
    cli.AddParameter("test");
    cli.Parse(argc, argv);

    jerobins::platform::Window *window =
        jerobins::platform::Window::Create("main");

    window->Show();
    window->BindOpenGL(NULL);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
      std::cout << glewError << std::endl;
      exit(EXIT_FAILURE);
    }

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    while (window->IsVisible()) {

      jerobins::common::Timer timer;
      timer.Start();
      window->HandleEvents();

      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT);

      // Use our shader
      // glUseProgram(programID);

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

      while(timer.Duration() < (1 * Seconds) / 30);
    }

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);

    window->UnbindOpenGL();
    window->Hide();
    delete window;
  } catch (std::runtime_error &e) {
    std::cout << std::string(e.what()) << std::endl;
  }

  return EXIT_SUCCESS;
}