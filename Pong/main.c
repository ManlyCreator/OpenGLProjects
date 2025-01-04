// Standard Libs
#include <cglm/vec3.h>
#include <stdio.h>
#include <math.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libs
#include <cglm/cglm.h>
#include "shader.h"
#include "texture.h"
#include "game.h"
#include "sprite.h"

// Macros
#define WIDTH 800
#define HEIGHT 600
#define PROJECTILE_SPEED 0.1

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float currentTime = 0, lastTime = 0, deltaTime;

// TODO: Finish spriteInit() function and draw using Sprite class
// TODO: Finish breakout section from LearnOpenGL

int main(void) {
  unsigned VAO, VBO, EBO;
  Shader shaderProgram;
  Texture texture;
  float vertices[] = {
    // Vertices     // Texutre Coords
    -0.01f, -0.01f, 0.0f, 0.0f,
     0.01f, -0.01f, 1.0f, 0.0f,
     0.01f,  0.01f, 1.0f, 1.0f,
    -0.01f,  0.01f, 0.0f, 1.0f
  };
  int indices[] = {
    0, 1, 2,
    0, 2, 3
  };
  GLFWwindow *window;

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

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

  // Vertex Array
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Element Buffer
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

  // Texture
  if (!textureConstruct(&texture, "../textures/awesomeface.png"))
    return -1;
  textureBind(texture);

  // Shader Program
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;
  shaderUse(shaderProgram);

  // Render Loop
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  mat4 model;
  mat4 projection;
  unsigned modelLoc = glGetUniformLocation(shaderProgram, "model");
  unsigned projectionLoc = glGetUniformLocation(shaderProgram, "projection");

  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Input
    processInput(window);

    // Render Commands
    glClearColor(0.0f, 0.0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glm_mat4_identity(model);
    glm_translate(model, (vec3){(glfwGetTime() * PROJECTILE_SPEED), 0.0f, 0.0f});
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

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

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
