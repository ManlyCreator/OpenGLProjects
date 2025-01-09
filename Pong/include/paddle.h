#ifndef PADDLE_H
#define PADDLE_H

#include "sprite.h"
#include <GLFW/glfw3.h>

#define PADDLE_WIDTH 50
#define PADDLE_HEIGHT 600
#define PADDLE_SIZE (vec2){PADDLE_WIDTH, PADDLE_HEIGHT}
#define PADDLE_POS_L (vec2){-WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2}
#define PADDLE_POS_R (vec2){WIDTH - PADDLE_WIDTH, (float)PADDLE_HEIGHT / 2 - (float)HEIGHT / 2}
#define PADDLE_SPEED 20.0f

typedef struct {
  Sprite base;
} Paddle;

void paddleMove(Sprite *sprite, int keys[], GLFWwindow *window);

#endif
