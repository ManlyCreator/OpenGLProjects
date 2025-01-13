// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "shader.h"

#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

int main(void) {
  unsigned shaderProgram;
  unsigned VAO, VBO;
  GLFWwindow *window;

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

  if (window == NULL)
  {
    printf("Window creation failed\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("GLAD initialization failed\n");
    return -1; 
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Vertex Array
  glGenVertexArrays(1, &VAO);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);
  
  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Render Commands
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    shaderUse(shaderProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clean-Up
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
