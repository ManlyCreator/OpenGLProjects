// Standard Libs
#include <stdio.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libs
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Macros
#define WIDTH 800
#define HEIGHT 600

void processInput(GLFWwindow *window);

// TODO: Render a small white square
// TODO: Tranform the square so that it moves at an angle
// TODO: Change the angle when the square collides with the screen borders

int main(void) {
  GLFWwindow *window;
  unsigned VAO, VBO, EBO;
  unsigned shaderProgram;
  float vertices[] = {
    -0.1f, -0.1f, 0.0f,
    -0.1f,  0.1f, 0.0f,
     0.1f,  0.1f, 0.0f,
     0.1,  -0.1f, 0.0,
  };
  int indices[] = {
    0, 1, 2,
    1, 2, 3
  };

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

  if (!window) {
    printf("Window Creation Failed\n");
    return -1;
  }

  glfwMakeContextCurrent(window);

  // GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("GLAD Initialization Failed\n");
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Vertex Array Object
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Element Buffer Object
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clear Memory
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
