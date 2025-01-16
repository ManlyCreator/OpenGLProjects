// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include <cglm/cglm.h>
#include "shader.h"
#include "cube.h"

#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

// TODO: Make a Cube library
// TODO: Render cube

int main(void) {
  unsigned VAO, VBO;
  unsigned shaderProgram;
  GLFWwindow *window;
  float vertices[] = {
    -1.0f,  1.0f, 0.0f, 
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
  };

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
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // Transformations
  mat4 projection, model; 
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f, projection);

  glm_mat4_identity(model);
  glm_translate(model, (vec4){0.0f, 0.0f, -3.0f});
  glm_rotate(model, glm_rad(-30.0f), (vec3){1.0f, 0.0f, 0.0f});
  glm_scale(model, (vec3){0.5f, 0.5f, 0.5f});


  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);
  
  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Render Commands
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Cube Transform
    glBindVertexArray(VAO);
    shaderUse(shaderProgram);
    shaderSetMatrix4(shaderProgram, "projection", projection);
    shaderSetMatrix4(shaderProgram, "model", model);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));

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
