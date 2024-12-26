#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define BUF_SIZE 512
#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
int shaderCompilationSuccess(unsigned shader);
int programLinkingSuccess(unsigned program);

int main(void) {
  GLFWwindow *window;
  unsigned vertexShader, fragmentShader1, fragmentShader2, shaderProgram1, shaderProgram2;
  unsigned VAOs[2], VBOs[2];
  float triangle1[] = {
    -1.0f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
  };
  float triangle2[] = {
     0.0f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     1.0f, -0.5f, 0.0f
  };
  const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    " gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);\n"
    "}\n";
  const char *fragmentShaderSource1 =
    "#version 330 core\n"
    "out vec4 fragCol;\n"
    "void main() {\n"
    " fragCol = vec4(1.0f, 0.7f, 0.1f, 1.0f);\n"
    "}\n";
  const char *fragmentShaderSource2 =
    "#version 330 core\n"
    "out vec4 fragCol;\n"
    "void main() {\n"
    " fragCol = vec4(1.0f, 0.1f, 0.4f, 1.0f);\n"
    "}\n";

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Excercises", NULL, NULL);

  if (!window) {
    printf("Window creation failed\n");
    return -1;
  }

  glfwMakeContextCurrent(window);

  // GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("GLAD initialization failed\n");
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Vertex Shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  if (!shaderCompilationSuccess(vertexShader))
    return -1;

  // Fragment Shader 1
  fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
  glCompileShader(fragmentShader1);
  if (!shaderCompilationSuccess(fragmentShader1))
    return -1;

  // Fragment Shader 2
  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentShader2);
  if (!shaderCompilationSuccess(fragmentShader2))
    return -1;

  // Program 1
  shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);

  // Program 2
  shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);
  if (!programLinkingSuccess(shaderProgram2))
    return -1;

  // Generating Buffers
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  // Vertex Data 1
  glBindVertexArray(VAOs[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

  // Vertex Data 2
  glBindVertexArray(VAOs[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

  // Callbacks
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Render Commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Triangle 1
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle1) / sizeof(triangle1[0]));
    // Triangle 2
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle2) / sizeof(triangle2[0]));

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int shaderCompilationSuccess(unsigned shader) {
  int success;
  char infoLog[BUF_SIZE];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, BUF_SIZE, NULL, infoLog);
    printf("*** SHADER COMPILATION ERROR ***\n%s", infoLog);
    return 0;
  }

  return 1;
}

int programLinkingSuccess(unsigned program) {
  int success;
  char infoLog[BUF_SIZE];

  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    glad_glGetProgramInfoLog(program, BUF_SIZE, NULL, infoLog);
    printf("*** PROGRAM LINKING ERROR ***\n%s", infoLog);
    return 0;
  }

  return 1;
}
