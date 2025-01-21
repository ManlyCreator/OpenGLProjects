// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// External Libraries
#include "scene.h"
#include "shader.h"
#include "utils.h"

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
void stackPush(mat4 matrix);
void stackPop(mat4 dest);
int stackGetTop(void);

unsigned stackTop = 0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 20.0f;
double currentTime;
mat4 projection;
mat4 matrixStack[NUM_MATRICES];

// TODO: Create a Moon object

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture sun, earth, moon;
  mat4 view, model;
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
  if (!(sun = textureLoad("../textures/sun.jpg")))
    return -1;
  if (!(earth = textureLoad("../textures/earth.jpg")))
    return -1;
  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);

  glm_mat4_identity(model);

  // Scene Setup
  scene = sceneInit(shaderProgram);

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

    // Sun
    scene.cube.texture = sun;
    stackPush(model);
    glm_translate(matrixStack[stackGetTop()], (vec3){0.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], sin(currentTime), (vec3){1.0f, 0.0f, 0.0f});
    sceneDraw(scene, CUBE, matrixStack[stackGetTop()]);
    stackPop(NULL);

    // Earth
    scene.cube.texture = earth;
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(matrixStack[stackGetTop()], (vec3){5.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], currentTime, (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(matrixStack[stackGetTop()], currentTime, (vec3){0.0f, 1.0f, 0.0f});
    sceneDraw(scene, CUBE, matrixStack[stackGetTop()]);
    stackPop(NULL);

    stackTop = 0;

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

void stackPush(mat4 matrix) {
  glm_mat4_copy(matrix, matrixStack[stackTop++]);
}

void stackPop(mat4 dest) {
  stackTop--;
  if (dest)
    glm_mat4_copy(matrixStack[stackTop], dest);
}

int stackGetTop() {
  return stackTop - 1;
}
