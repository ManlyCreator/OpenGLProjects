// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// OpenGL Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include <shader.h>

/*** EXCERCISE QUESTION ***/
// The left side is always black because it oscillates between -1 & 0, which produces black.

#define WIDTH 800
#define HEIGHT 600
#define BUF_SIZE 512
#define WIREFRAME_MODE 0

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

int main(void) {
  unsigned VBO, EBO, VAO;
  Shader shaderProgram;
  float vertices[] = {
    // Vertices         // Colors
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };
  const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec3 fragColIn;\n"
    "out vec3 fragColOut;\n"
    "void main() {\n"
    "  gl_Position = vec4(pos, 1.0f);\n"
    "  fragColOut = fragColIn;\n"
    "}\n";
  const char *fragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 fragColOut;\n"
    "out vec4 col;\n"
    "void main() {\n"
    "  col = vec4(fragColOut, 1.0f);\n"
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

  // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Setting Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

  // Program Creation
  if (!shaderConstruct(&shaderProgram, "../vertex.glsl", "../fragment.glsl"))
    return -1;
  shaderUse(shaderProgram);

  // Callbacks
  glfwSetKeyCallback(window, keyCallback); 
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Enables Wireframe Rendering
#if WIREFRAME_MODE
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Render Commands
    float offset = sin(glfwGetTime());
    shaderSetFloat(shaderProgram, "xOffset", offset);
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
