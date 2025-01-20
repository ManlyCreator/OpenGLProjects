// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// External Libraries
#include "scene.h"
#include "utils.h"

#define WIDTH 1000
#define HEIGHT 1000

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;
double currentTime;

// TODO: Create a Shape struct and typedef each shape to the struct

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture checker;
  mat4 projection, view;
  GLFWwindow *window;
  Scene scene;

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
  if (!(checker = textureLoad("../textures/checkerboard.jpg")))
    return -1;
  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);


  glm_mat4_identity(view);
  glm_translate(view, (vec3){-cameraX, -cameraY, -cameraZ});

  // Scene Setup
  scene = sceneInit(shaderProgram);
  glm_vec3((vec4){1.0f, 1.0f, 0.0f, 1.0f}, scene.pyramid.position);
  glm_vec3((vec4){0.5f, 0.5f, 0.5f, 1.0f}, scene.pyramid.size);
  scene.pyramid.texture = 0;

  glm_vec3((vec4){0, -1.0f, 0.0f, 1.0f}, scene.cube.position);
  glm_vec3((vec4){10.0f, 0.5f, 20.0f, 1.0f}, scene.cube.size);
  scene.cube.texture = checker;

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
    shaderSetMatrix4(shaderProgram, "view", view);
    shaderSetFloat(shaderProgram, "currentTime", currentTime);

    // Pyramid
    scene.pyramid.rotation[0] = sin(currentTime * 2) * 30.0f;
    scene.pyramid.rotation[1] = currentTime * 50.0f;
    sceneDraw(scene, PYRAMID);

    // Cube
    sceneDraw(scene, CUBE);

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
