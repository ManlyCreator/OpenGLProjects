// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include <cglm/cglm.h>
#include "shader.h"
#include "scene.h"

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

void stackPush(mat4 matrix);
void stackPop(void);
int stackGetTop(void);

unsigned stackTop = 0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 10.0f;
double currentTime;
mat4 projection;
mat4 matrixStack[NUM_MATRICES];

// TODO: Pg. 101, Excercise 4.4

int main(void) {
  double timeFactor;
  unsigned shaderProgram;
  mat4 view;
  GLFWwindow *window;
  Scene scene;

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  // Shader
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Projection Matrix
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);

  // Scene Setup
  scene = sceneInit(shaderProgram);

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

    /*** MATRIX STACK ***/
    // View
    stackPush(view);
    glm_mat4_identity(view);
    glm_rotate(matrixStack[stackGetTop()], glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(view, (vec3){-cameraX, -cameraY, -cameraZ});
    shaderSetMatrix4(shaderProgram, "view", view);
    stackPop();

    // Sun (Pyramid)
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(matrixStack[stackGetTop()], (vec3){0.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], glm_rad(sin(currentTime * 2) * 20.0f), (vec3){1.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], currentTime * 2, (vec3){0.0f, 1.0f, 0.0f});
    shaderSetMatrix4(shaderProgram, "model", matrixStack[stackGetTop()]);
    pyramidDraw(scene);

    // Planet 1 (Big Cube)
    stackPop(); stackPop();
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(matrixStack[stackGetTop()], (vec3){4.0f, 0.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], currentTime * 0.5, (vec3){0.0f, 1.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_scale(matrixStack[stackGetTop()], (vec3){0.5f, 0.5f, 0.5f});
    shaderSetMatrix4(shaderProgram, "model", matrixStack[stackGetTop()]);
    cubeDraw(scene);

    // Moon (Little Cube)
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(matrixStack[stackGetTop()], (vec3){0.0f, sin(currentTime * 0.5) * 3.0f, cos(currentTime * 0.5) * 3.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], currentTime * 0.5, (vec3){0.0f, 1.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_scale(matrixStack[stackGetTop()], (vec3){0.5f, 0.5f, 0.5f});
    shaderSetMatrix4(shaderProgram, "model", matrixStack[stackGetTop()]);
    cubeDraw(scene);

    // Planet 2 (Bipyramid)
    stackPop(); stackPop(); stackPop(); stackPop(); stackPop();
    stackPush(matrixStack[stackGetTop()]);
    glm_translate(matrixStack[stackGetTop()], (vec3){-8.0f, sin(currentTime) * 5.0f, cos(currentTime) * 5.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], currentTime, (vec3){0.0f, 1.0f, 0.0f});
    stackPush(matrixStack[stackGetTop()]);
    glm_rotate(matrixStack[stackGetTop()], glm_rad(45.0f), (vec3){0.0f, 0.0f, 1.0f});
    shaderSetMatrix4(shaderProgram, "model", matrixStack[stackGetTop()]);
    bipyramidDraw(scene);

    // Reset Stack
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

void stackPop(void) {
  stackTop--;
}

int stackGetTop() {
  return stackTop - 1;
}
