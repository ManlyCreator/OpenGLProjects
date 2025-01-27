// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "matrixStack.h"
#include "shape.h"
#include "pyramid.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 20.0f;
double currentTime;
mat4 projection;

// TODO: Rotate each ring of the Torus to match the horizontal rotation

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture sun, earth, moon;
  mat4 view, model;
  GLFWwindow *window;
  Sphere sphere;
  Torus torus;
  MStack stack = mStackInit();

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

  if (window == NULL) {
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

  // Textures
  if (!(sun = textureLoad("../textures/sun.jpg")))
    return -1;
  if (!(earth = textureLoad("../textures/earth.jpg")))
    return -1;
  if (!(moon = textureLoad("../textures/moon.jpg")))
    return -1;
  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);

  // Sphere
  sphere = sphereInit(10, 10, &shaderProgram, NULL);

  // Torus
  torus = torusInit(10, &shaderProgram, &moon);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);
  
  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    // Render Commands
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderSetMatrix4(shaderProgram, "projection", projection);
    shaderSetFloat(shaderProgram, "currentTime", currentTime);

    // View
    glm_mat4_identity(view);
    glm_lookat((vec3){cameraX, cameraY, cameraZ}, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, view);
    shaderSetMatrix4(shaderProgram, "view", view);

    // Sphere
    glm_mat4_identity(model);
    glm_translate(model, (vec3){0.0f, 0.0f, 3.0f});
    glm_rotate(model, currentTime * 1.0f, (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(model, glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});
    glm_scale(model, (vec3){2.0f, 2.0f, 2.0f});
    /*shapeDraw(sphere, model);*/
    shapeDraw(torus, model);


    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clean-Up
  shapeDelete(&sphere);
  glfwTerminate();

  return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)width / height, 0.1f, 200.0f, projection);
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
