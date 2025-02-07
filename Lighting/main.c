// Standard C Libraries
#include <stdio.h>
#include <stdbool.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "camera.h"
#include "materials.h"
#include "texture.h"
#include "shader.h"
#include "matrixStack.h"
#include "torus.h"
#include "shape.h"
#include "cube.h"

#define WIDTH 1000
#define HEIGHT 1000

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void cursorPosCallback(GLFWwindow *window, double x, double y);
void processInput(GLFWwindow *window);
void lookAt(vec3 pos, vec3 target, vec3 up, mat4 lookAtMat);

double currentTime;
mat4 projection;

double lastX, lastY;
double deltaX, deltaY;

Camera camera;

// TODO: LearnOpenGL - Basic Lighting: One last thing

int main(void) {
  int width, height;
  double timeFactor;
  Shader objectShader, lightShader;
  Texture saturn, saturnRing;
  mat4 view, model;
  GLFWwindow *window;
  Torus torus;
  Cube lightSource;
  MStack stack = mStackInit();
  float *ambient = pearlAmbient();
  vec3 lightPos = {-5.0f, 10.0f, 0.0f};
  vec3 lightColor = {1.0f, 1.0f, 1.0f};
  vec3 torusColor = {1.0f, 0.5f, 0.31f};
  vec3 torusPositions[] = {
      { 0.0f,   0.0f,   0.0f}, 
      { 20.0f,  5.0f,  30.0f}, 
      {-10.5f, -2.2f, -20.5f},  
      {-30.8f, -2.0f,  30.3f},  
      { 20.4f, -0.4f, -30.5f},  
      {-10.7f,  3.0f,  15.5f},  
      { 10.3f, -2.0f, -20.5f},  
      { 10.5f,  2.0f,  20.5f}, 
      { 10.5f,  0.2f, -10.5f}, 
      {-10.3f,  1.0f,  25.5f}  
  };

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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
  // Shaders
  if (!shaderConstruct(&objectShader, "../shaders/objectVertexShader.glsl", "../shaders/objectFragmentShader.glsl"))
    return -1;
  if (!shaderConstruct(&lightShader, "../shaders/lightCubeVertexShader.glsl", "../shaders/lightCubeFragmentShader.glsl"))
    return -1;
  
  // Camera
  camera = cameraInit((vec3){0.0f, 0.0f, 20.0f}, 0.0f, glm_rad(-90.0f));

  // Transformations
  glm_mat4_identity(projection);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f, projection);

  torus = torusInit(50, 50, 2.0f, 1.0f, torusColor, &objectShader, NULL);
  lightSource = cubeInit(lightColor, &lightShader, NULL);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  // Sets lastX & lastY to center of screen for proper delta calculation
  glfwGetWindowSize(window, &width, &height);
  lastX = (float)width / 2;
  lastY = (float)height / 2;
  glfwSetCursorPosCallback(window, cursorPosCallback);

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();

    // Input
    processInput(window);

    // Render Commands
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Object Shader
    shaderUse(objectShader);
    shaderSetMatrix4(objectShader, "projection", projection);
    cameraUpdateView(&camera);
    shaderSetMatrix4(objectShader, "view", camera.view);
    shaderSetVector3f(objectShader, "lightColor", lightColor);
    shaderSetVector3f(objectShader, "lightPos", lightPos);
    for (int i = 0; i < 10; i++) {
      glm_mat4_identity(model);
      glm_translate(model, torusPositions[i]);
      glm_rotate(model, glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});
      glm_rotate(model, glm_rad(-10.0f + i * 5.0f), (vec3){0.0f, 0.0f, 1.0f});
      glm_scale(model, (vec3){1.0f, 1.0f, 1.0f});
      shapeDraw(torus, model);
    }

    // Light Cube Shader
    shaderUse(lightShader);
    shaderSetMatrix4(lightShader, "projection", projection);
    shaderSetMatrix4(lightShader, "view", camera.view);
    glm_mat4_identity(model);
    glm_translate(model, lightPos);
    shapeDraw(lightSource, model);


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

void cursorPosCallback(GLFWwindow *window, double x, double y) {
  deltaX = x - lastX;
  deltaY = (y - lastY) * -1;

  cameraProcessMouse(&camera, deltaX, deltaY);

  lastX = x;
  lastY = y;
}

void processInput(GLFWwindow *window) {
  static vec3 newCameraFront;

  // Exit
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // Camera Controls
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, RIGHT);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, LEFT);
}

void lookAt(vec3 pos, vec3 target, vec3 up, mat4 lookAtMat) {
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
