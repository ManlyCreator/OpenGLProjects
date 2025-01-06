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
#define BALL_WIDTH 20
#define BALL_SIZE (vec2){BALL_WIDTH, BALL_WIDTH}
#define BALL_POS (vec2){-(float)BALL_WIDTH / 2, -(float)BALL_WIDTH / 2}
#define BALL_VELOCITY (vec2){5.0f, 10.0f}
#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 300
#define PADDLE_SIZE (vec2){PADDLE_WIDTH, PADDLE_HEIGHT}
#define PADDLE_POS_L (vec2){-WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2}

// Main
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float currentTime = 0, lastTime = 0, deltaTime;

int main(void) {
  Shader shaderProgram;
  Texture texture;
  Sprite ball;
  Sprite paddleL, paddleR;
  mat4 projection;
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

  // Texture
  if (!textureConstruct(&texture, "../textures/awesomeface.png"))
    return -1;

  // Shader Program
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl"))
    return -1;

  // Sprites
  spriteConstruct(&ball, shaderProgram, 0, BALL_SIZE, BALL_POS, (vec2){1.0f, 10.0f});
  spriteConstruct(&paddleL, shaderProgram, 0, PADDLE_SIZE, PADDLE_POS_L, (vec2){0.0f, 0.0f});
  spriteConstruct(
      &paddleR, shaderProgram, 0, (vec2){PADDLE_WIDTH, PADDLE_HEIGHT},
      (vec2){(float)WIDTH - (float)PADDLE_WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2},
      (vec2){0.0f, 0.0f} 
  );

  // Projection Matrix
  glm_ortho(-WIDTH, WIDTH, -HEIGHT, HEIGHT, -1.0f, 1.0f, projection);

  // Render Loop
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Input
    processInput(window);

    // Render Commands
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderSetMatrix4(shaderProgram, "projection", projection);
    spriteMove(&ball);
    spriteDraw(ball, 0.0f, (vec3){1.0f, 1.0f, 1.0f});
    spriteDraw(paddleL, 0.0f, (vec3){1.0f, 1.0f, 1.0f});
    spriteDraw(paddleR, 0.0f, (vec3){1.0f, 1.0f, 1.0f});

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
