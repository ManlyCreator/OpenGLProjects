// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "texture.h"
#include "shader.h"
#include "matrixStack.h"
#include "model.h"
#include "torus.h"
#include "sphere.h"
#include "shape.h"

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 20.0f;
double currentTime;
mat4 projection;

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture saturn, saturnRing;
  mat4 view, model;
  GLFWwindow *window;
  Torus torus;
  Sphere sphere;
  Model object;
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
  if (!(saturn = textureLoad("../textures/saturn.jpg")))
    return -1;
  if (!(saturnRing = textureLoad("../textures/saturn_ring.jpg")))
    return -1;
  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);

  // Model
  sphere = sphereInit(50, 50, &shaderProgram, &saturn);
  torus = torusInit(50, 2, 1.5f, 0.2f, &shaderProgram, &saturnRing);
  object = modelInit("../models/shuttle.obj", &shaderProgram, NULL);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);
  
  // Render Loop
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

    glm_mat4_identity(model);
    glm_scale(model, (vec3){0.5f, 0.5f, 0.5f});
    glm_translate(model, (vec3){0.0f, 0.0f, 0.0f});
    glm_rotate(model, currentTime * 1.0f, (vec3){1.0f, 1.0f, 0.0f});
    modelDraw(object, model);
    /*// Saturn*/
    /*glm_mat4_identity(model);*/
    /*mStackPush(&stack, model);*/
    /*glm_scale(mStackGet(&stack), (vec3){1.5f, 1.5f, 1.5f});*/
    /*glm_translate(mStackGet(&stack), (vec3){0.0f, 0.0f, 0.0f});*/
    /*mStackPush(&stack, mStackGet(&stack));*/
    /*glm_rotate(mStackGet(&stack), currentTime * 1.0f, (vec3){0.0f, 1.0f, 0.0f});*/
    /*glm_rotate(mStackGet(&stack), glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});*/
    /*mStackPush(&stack, mStackGet(&stack));*/
    /*glm_rotate(mStackGet(&stack), currentTime * 0.5f, (vec3){0.0f, 1.0f, 0.0f});*/
    /*shapeDraw(sphere, mStackGet(&stack));*/
    /*mStackPop(&stack, NULL);*/
    /**/
    /*// Ring*/
    /*mStackPush(&stack, mStackGet(&stack));*/
    /*glm_rotate(mStackGet(&stack), -currentTime * 1.0f, (vec3){0.0f, 1.0f, 0.0f});*/
    /*shapeDraw(torus, mStackGet(&stack));*/
    /*mStackPop(&stack, NULL);*/
    /**/
    /*// Shuttle*/
    /*mStackPop(&stack, NULL);*/
    /*mStackPush(&stack, mStackGet(&stack));*/
    /*glm_scale(mStackGet(&stack), (vec3){0.05f, 0.05f, 0.05f});*/
    /*glm_rotate(mStackGet(&stack), glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});*/
    /*glm_rotate(mStackGet(&stack), glm_rad(currentTime * 100.0f), (vec3){0.0f, 1.0f, 0.0f});*/
    /*glm_translate(mStackGet(&stack), (vec3){0, 0.0f, 60.0f});*/
    /*glm_rotate(mStackGet(&stack), glm_rad(-90.0f), (vec3){0.0f, 1.0f, 0.0f});*/
    /*modelDraw(object, mStackGet(&stack));*/
    /**/
    /**/
    /*// Reset*/
    /*mStackClear(&stack);*/

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
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)width / height, 0.1f, 200.0f, projection);
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
