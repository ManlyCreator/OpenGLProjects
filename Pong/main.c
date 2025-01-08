// Standard Libs
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libs
#include "game.h"
#include "ball.h"
#include "paddle.h"

// Main
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int gameStart = 0;
float angles[] = { 30.0f, 45.0f, 100.0f, 135.0f, 300.0f, };

// TODO: Detect which edge gets hit with the ball to properly calculate which way to adjust velocity

int main(void) {
  float ballAngle;
  Shader shaderProgram;
  Texture texture;
  Ball ball;
  Paddle paddleL, paddleR;
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

  // Ball Setup
  srand(time(NULL));
  ballAngle = angles[rand() % (sizeof(angles) / sizeof(angles[0]))];
  spriteConstruct(&ball.base, shaderProgram, 0, BALL_SIZE, BALL_POS, BALL_VELOCITY(ballAngle));

  // Player Setup
  spriteConstruct(&paddleL.base, shaderProgram, 0, PADDLE_SIZE, PADDLE_POS_L, (vec2){0.0f, 0.0f});
  spriteConstruct(&paddleR.base, shaderProgram, 0, PADDLE_SIZE, PADDLE_POS_R, (vec2){0.0f, 0.0f});

  // Projection Matrix
  glm_ortho(-WIDTH, WIDTH, -HEIGHT, HEIGHT, -1.0f, 1.0f, projection);

  // Render Loop
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  while (!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    // *** RENDER COMMANDS ***
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderSetMatrix4(shaderProgram, "projection", projection);
    // Game Logic
    if (gameStart) {
      ballMove(&ball, (Paddle[]){paddleL, paddleR});
      paddleMove(&paddleL.base, (int[]){GLFW_KEY_W, GLFW_KEY_S}, window);
      paddleMove(&paddleR.base, (int[]){GLFW_KEY_UP, GLFW_KEY_DOWN}, window);
      if (!ball.inBounds) {
        ballAngle = angles[rand() % (sizeof(angles) / sizeof(angles[0]))];
        gameStart = 0;
      }
    } else {
      glm_vec2_copy(BALL_POS, ball.base.position);
      glm_vec2_copy(BALL_VELOCITY(ballAngle), ball.base.velocity);
      glm_vec2_copy(PADDLE_POS_L, paddleL.base.position);
      glm_vec2_copy(PADDLE_POS_R, paddleR.base.position);
    }
    spriteDraw(ball.base, 0.0f, (vec3){1.0f, 1.0f, 1.0f});
    spriteDraw(paddleL.base, 0.0f, (vec3){1.0f, 1.0f, 1.0f});
    spriteDraw(paddleR.base, 0.0f, (vec3){1.0f, 1.0f, 1.0f});

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
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    gameStart = 1;
}
