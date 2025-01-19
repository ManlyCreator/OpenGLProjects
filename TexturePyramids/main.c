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

#define WIDTH 1000
#define HEIGHT 1000

// TODO: Rework library to render pyramids
// TODO: Implement textures

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 50.0f;
double currentTime;

int main(void) {
  double timeFactor;
  unsigned shaderProgram;
  mat4 projection, view;
  GLFWwindow *window;
  Cube cube;

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

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);


  glm_mat4_identity(view);
  glm_translate(view, (vec3){-cameraX, -cameraY, -cameraZ});

  cube = cubeInit(shaderProgram, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.5f, 0.5f, 0.5f}, (vec3){-45.0f, 0.0f, 0.0f});

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);
  
  glEnable(GL_DEPTH_TEST);
  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    // Render Commands
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderSetMatrix4(shaderProgram, "projection", projection);
    shaderSetMatrix4(shaderProgram, "view", view);
    shaderSetFloat(shaderProgram, "currentTime", currentTime);

    cubeDraw(cube, 10);

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
