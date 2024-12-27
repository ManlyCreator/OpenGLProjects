#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define BUF_SIZE 512

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int shaderCompilationSuccess(unsigned shader);
int programLinkingSuccess(unsigned program);

// TODO: Hello Triangle - Element Buffer Objects

int main(void) {
  unsigned VAO, VBO;
  unsigned vertexShader, fragmentShader;
  unsigned program;
  float vertices[] = {
    // First Triangle
    -1.0f, -0.5f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f, // Top
     0.0f, -0.5f, 0.0f, // Bottom Right
    // Second Triangle
    0.0f, -0.5f, 0.0f, // Bottom Left
    0.5f,  0.5f, 0.0f, // Top
    1.0f, -0.5f, 0.0f  // Bottom Right
  };
  const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);\n"
    "}\n";
  const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 fragCol;\n"
    "void main() {\n"
    "    fragCol = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";
  GLFWwindow *window;

  // Initializes GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Initializes window information
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLProject1", NULL, NULL);

  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // Loads OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  // Initializes viewport settings
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  // Generating Vertex Array
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Generating Vertex Buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Specifying Vertex Buffer Data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Vertex Shader Compilation
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  if (!shaderCompilationSuccess(vertexShader))
    return -1;

  // Fragment Shader Compilation
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  if (!shaderCompilationSuccess(fragmentShader))
    return -1;

  // Program Creation
  int success;
  char infoLog[BUF_SIZE];

  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  if (!programLinkingSuccess(program))
    return -1;

  glUseProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  /*** RENDER LOOP ***/
  while (!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    // Rendering Commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
    
    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int shaderCompilationSuccess(unsigned shader) {
  int success;
  char infoLog[BUF_SIZE];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, BUF_SIZE, NULL, infoLog);
    printf("*** SHADER COMPILATION ERROR ***\n");
    printf("%s", infoLog);
  }

  return success;
}

int programLinkingSuccess(unsigned program) {
  int success;
  char infoLog[BUF_SIZE];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, BUF_SIZE, NULL, infoLog);
    printf("*** PROGRAM LINKING ERROR ***\n");
    printf("%s", infoLog);
  }

  return success;
}
