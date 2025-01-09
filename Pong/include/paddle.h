#ifndef PADDLE_H
#define PADDLE_H

#include "sprite.h"
#include <GLFW/glfw3.h>

#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 300
#define PADDLE_SIZE (vec2){PADDLE_WIDTH, PADDLE_HEIGHT}
#define PADDLE_POS_L (vec3){-WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2}
#define PADDLE_POS_R (vec3){WIDTH - PADDLE_WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2, 0.0f}
#define PADDLE_SPEED 20.0f

typedef struct {
  Sprite base;
} Paddle;

void paddleMove(Sprite *sprite, int keys[], GLFWwindow *window);

#endif
