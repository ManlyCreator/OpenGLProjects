#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define BUF_SIZE 512

// TODO: Create a GitHub repo that ignores all build directories
// TODO: Hello Window - Element Buffer Objects ; Render two separate triangles using EBOs

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
int shaderCompilationSuccess(unsigned shader);
int programLinkSuccess(unsigned program);

int main(void) {
  unsigned VBO, VAO;
  unsigned vertexShader, fragmentShader, shaderProgram;
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };
  const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);\n"
    "}\n";
  const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 col;\n"
    "void main() {\n"
    "    col = vec4(1.0f, 0.75f, 0.25f, 1.0f);\n"
    "}\n";
  GLFWwindow *window;

  // GLFW Initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window Creation
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLProject2", NULL, NULL);
  if (!window) {
    printf("*** WINDOW CREATION FAILED ***\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  // GLAD Initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("*** GLAD INITIALIZATION FAILED ***\n");
    return -1;
  }
  glViewport(0, 0, WIDTH, HEIGHT);

  // Vertex Array Buffer
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Setting Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // Vertex Shader 
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  if (!shaderCompilationSuccess(vertexShader))
    return -1;

  // Fragment Shader 
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  if (!shaderCompilationSuccess(fragmentShader))
    return -1;

  // Shader Program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  if (!programLinkSuccess(shaderProgram))
    return -1;
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Callbacks
  glfwSetKeyCallback(window, keyCallback); 
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Process Input

    // Render Commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();

  return 0;
}

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int shaderCompilationSuccess(unsigned shader) {
  int success;
  char infoLog[BUF_SIZE];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, BUF_SIZE, NULL, infoLog);
    printf("*** ERROR COMPILING SHADER ***\n%s", infoLog);
    return 0;
  }
  return 1;
}

int programLinkSuccess(unsigned program) {
  int success;
  char infoLog[BUF_SIZE];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, BUF_SIZE, NULL, infoLog);
    printf("*** ERROR LINKING PROGRAM ***\n%s", infoLog);
    return 0;
  }
  return 1;
}
