#include "paddle.h"

void paddleMove(Sprite *sprite, int keys[], GLFWwindow *window) {
  glm_vec2_add(sprite->position, sprite->velocity, sprite->position);
  if (glfwGetKey(window, keys[0]) == GLFW_PRESS && sprite->position[1] + sprite->size[1] < HEIGHT)
    sprite->velocity[1] = PADDLE_SPEED;
  else if (glfwGetKey(window, keys[1]) == GLFW_PRESS && sprite->position[1] > -HEIGHT) 
    sprite->velocity[1] = -PADDLE_SPEED;
  else
   sprite->velocity[1] = 0;
}
