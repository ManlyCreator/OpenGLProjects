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

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 20.0f;
double currentTime;
mat4 projection;

// TODO: Clean up project

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture sun, earth, moon;
  mat4 view, model;
  GLFWwindow *window;
  Sphere sphere;
  Cube cube;
  Pyramid pyramid;
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

  glm_mat4_identity(model);

  // Sphere
  sphere = sphereInit(20, 20, shaderProgram, 0);

  // Cube
  cube = cubeInit(shaderProgram, 0);

  // Pyramid
  pyramid = pyramidInit(shaderProgram, 0);

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

    // Cube
    glm_vec3_copy((vec3){-5.0f, 5.0f, 0.0f}, cube.position);
    glm_vec3_copy((vec3){currentTime * 20.0f, currentTime * 20.0f, 0.0f}, cube.rotation);
    glm_vec3_copy((vec3){1.5f, 1.5f, 1.5f}, cube.size);
    shapeTranslate(cube, cube.position, cube.rotation, cube.size, model);
    shapeDraw(cube, model);

    // Pyramid
    glm_vec3_copy((vec3){-5.0f, -5.0f, 0.0f}, pyramid.position);
    glm_vec3_copy((vec3){0.0f, currentTime * 20.0f, 0.0f}, pyramid.rotation);
    glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, pyramid.size);
    shapeTranslate(pyramid, pyramid.position, pyramid.rotation, pyramid.size, model);
    shapeDraw(pyramid, model);

    // Sun
    sphere.texture = sun;
    glm_mat4_identity(model);
    mStackPush(&stack, model);
    glm_translate(mStackGet(&stack), (vec3){0.0f, 0.0f, 0.0f});
    mStackPush(&stack, mStackGet(&stack));
    glm_rotate(mStackGet(&stack), currentTime, (vec3){0.0f, 1.0f, 0.0f});
    glm_scale(mStackGet(&stack), (vec3){2.0f, 2.0f, 2.0f});
    shapeDraw(sphere, mStackGet(&stack));
    mStackPop(&stack, NULL);

    // Earth
    sphere.texture = earth;
    mStackPush(&stack, mStackGet(&stack));
    glm_translate(mStackGet(&stack), (vec3){5.0f, 0.0f, 0.0f});
    glm_rotate(mStackGet(&stack), currentTime, (vec3){1.0f, 1.0f, 0.0f});
    mStackPush(&stack, mStackGet(&stack));
    glm_scale(mStackGet(&stack), (vec3){1.5f, 1.5f, 1.5f});
    shapeDraw(sphere, mStackGet(&stack));
    mStackPop(&stack, NULL);

    // Moon
    sphere.texture = moon;
    mStackPush(&stack, mStackGet(&stack));
    glm_translate(mStackGet(&stack), (vec3){sin(currentTime * 0.5) * 2.0f, cos(currentTime * 0.5) * 2.0f, sin(currentTime * 0.5) * 2.0f});
    glm_rotate(mStackGet(&stack), currentTime, (vec3){0.0f, 1.0f, 0.0f});
    glm_scale(mStackGet(&stack), (vec3){0.5f, 0.5f, 0.5f});
    shapeDraw(sphere, mStackGet(&stack));

    mStackClear(&stack);

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clean-Up
  shapeDelete(&sphere);
  shapeDelete(&cube);
  shapeDelete(&pyramid);
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
