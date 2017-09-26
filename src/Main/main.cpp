
// StdLib
#include <iostream>
#include <fstream>

// Jerobins
#include <Common/CommandLineArguments.hpp>
#include <Common/Configuration.hpp>
#include <Common/Constants.hpp>
#include <Common/Timer.hpp>
#include <Platform/Window.hpp>
#include <Render/OpenGL.hpp>
#include <Resource/BlenderLoader.hpp>

// Convert a frame duration to frames per seconds
float DurationToFPS(double milliseconds) {
  return (float)((1.0 * Seconds) / milliseconds);
}

// Convert frames per second to duration of single frame.
float FPSToDuration(double fps) {
  return (float)((1.0 * Seconds) / fps);
}

// Cap the duration to a certain frames per second
void CapFramesPerSeconds(float fps, jerobins::common::Timer & timer) {
  while (timer.Duration() <= FPSToDuration(fps) ) {
  }
}

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path) {

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()) {
    std::string Line = "";
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  } else {
    printf("Impossible to open %s. Are you in the right directory ? Don't "
           "forget to read the FAQ !\n",
           vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open()) {
    std::string Line = "";
    while (getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const *VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const *FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
                       &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}

// OpenGL variables
static GLuint VertexArrayID;
static GLuint vertexbuffer;
static GLuint programID;

void setupOpenGL() {

  if (!gladLoadGL()) {
    std::cout << "could not load opengl" << std::endl;
    exit(-1);
  }

  if(GLVersion.major == 0) {
    std::cout << "Invalid OpenGL Version " << GLVersion.major << "." << GLVersion.minor << std::endl;
    exit(-1);
  }

  // OpenGL items
  programID = LoadShaders("shaders/vertex/passthrough.vert", "shaders/fragment/red.frag");

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

  glUseProgram(programID);

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
}

void cleanupOpenGL() {
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
}

/**/
int main(int argc, char *argv[]) {

  jerobins::resource::BlenderLoader::LoaderTest();

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

    setupOpenGL();

    while (window->IsVisible()) {

      jerobins::common::Timer timer;
      timer.Start();
      window->HandleEvents();

      drawOpenGL();

      window->SwapBuffer();

      switch (glGetError()) {
      case GL_NO_ERROR:
        break;
      case GL_INVALID_ENUM:
        std::cout << "Invalid enum!" << std::endl;
        exit(1);
        break;
      case GL_INVALID_VALUE:
        std::cout << "Invalid value!" << std::endl;
        exit(1);
        break;
      case GL_INVALID_OPERATION:
        std::cout << "Invalid operation!" << std::endl;
        exit(1);
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cout << "Invalid Framebuffer operation!" << std::endl;
        exit(1);
        break;
      case GL_OUT_OF_MEMORY:
        std::cout << "Out of memory on GPU!" << std::endl;
        exit(1);
        break;
      default:
        std::cout << "Unknown OpenGL occurred!" << std::endl;
        exit(1);
        break;
      }

      CapFramesPerSeconds(64, timer);
      timer.Stop();
      std::cout << "FPS: " << DurationToFPS((double)timer.Duration()) << std::endl;
    }

    cleanupOpenGL();

    window->UnbindOpenGL();
    window->Hide();
    delete window;

  } catch (std::runtime_error &e) {
    std::cout << std::string(e.what()) << std::endl;
  }

  return EXIT_SUCCESS;
}