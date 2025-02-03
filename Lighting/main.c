// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "materials.h"
#include "texture.h"
#include "shader.h"
#include "matrixStack.h"
#include "torus.h"
#include "shape.h"

#define WIDTH 1000
#define HEIGHT 1000
#define NUM_MATRICES 100

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
void lookAt(vec3 pos, vec3 target, mat4 lookAtMat);

float cameraX = -10.0f, cameraY = 10.0f, cameraZ = 20.0f;
double currentTime;
mat4 projection;

// TODO: Learn OpenGL - Camera: Walk Around

int main(void) {
  double timeFactor;
  Shader shaderProgram;
  Texture saturn, saturnRing;
  mat4 view, model;
  GLFWwindow *window;
  Torus torus;
  MStack stack = mStackInit();
  float *ambient = pearlAmbient();
  printf("ambient = { %f, %f, %f, %f }\n", ambient[0], ambient[1], ambient[2], ambient[3]);

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

  torus = torusInit(50, 50, 2.0f, 1.0f, &shaderProgram, NULL);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, keyCallback);

  // Manual LookAt
  lookAt((vec3){cameraX, cameraY, cameraZ}, (vec3){0.0f, 0.0f, 0.0f}, view);
  glm_mat4_print(view, stdout);

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
    shaderSetMatrix4(shaderProgram, "view", view);

    // Model
    glm_mat4_identity(model);
    glm_translate(model, (vec3){1.0f, 1.0f, 1.0f});
    glm_rotate(model, glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(model, glm_rad(-10.0f), (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(model, (vec3){1.0f, 1.0f, 1.0f});
    shapeDraw(torus, model);

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

void lookAt(vec3 pos, vec3 target, mat4 lookAtMat) {
  vec3 up = {0.0f, 1.0f, 0.0f};
  vec3 negObjectDirection;
  vec3 objectRight, objectUp;
  mat4 transformMat;

  // (Negative) Direction Vector
  glm_vec3_sub(pos,  target, negObjectDirection);
  glm_vec3_normalize(negObjectDirection);

  // Right Vector
  glm_vec3_cross(up, negObjectDirection, objectRight);
  glm_vec3_normalize(objectRight);

  // Up Vector
  glm_vec3_cross(negObjectDirection, objectRight, objectUp);

  // Rotation Matrix
  mat4 rotationMat = {
    {objectRight[0], objectUp[0], negObjectDirection[0], 0.0f},
    {objectRight[1], objectUp[1], negObjectDirection[1], 0.0f},
    {objectRight[2], objectUp[2], negObjectDirection[2], 0.0f},
    {0.0f,           0.0f,        0.0f,         1.0f}
  };

  // Transformation Matrix
  glm_mat4_identity(transformMat);
  transformMat[3][0] = -pos[0];
  transformMat[3][1] = -pos[1];
  transformMat[3][2] = -pos[2];

  // LookAt Matrix
  glm_mat4_mul(rotationMat, transformMat, lookAtMat);
}
