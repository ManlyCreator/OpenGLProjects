#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
  unsigned VAO, VBO;
  unsigned shaderProgram;
  GLFWwindow *window;
  float vertices[] = {
    // Vertex Coordinates // Color Coordinates
    -0.5f, -0.5f,         1.0f, 0.0f, 0.0f, 
     0.0f,  0.5f,         0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,         0.0f, 0.0f, 1.0f
  };

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

  if (!window) {
    printf("*** WINDOW CREATION FAILED ***\n");
    return -1;
  }

  glfwMakeContextCurrent(window);

  // GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("*** GLAD INITIALIZATION FAILED ***\n");
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Vertex Array Data
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;
  shaderUse(shaderProgram);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}
