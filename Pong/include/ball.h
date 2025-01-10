#ifndef BALL_H
#define BALL_H

#include "sprite.h"
#include "paddle.h"

#define BALL_WIDTH 20
#define BALL_SIZE (vec2){BALL_WIDTH, BALL_WIDTH}
#define BALL_POS (vec3){-(float)BALL_WIDTH / 2, -(float)BALL_WIDTH / 2}
#define BALL_SPEED 20
#define BALL_VELOCITY(angle) (vec2){cos(glm_rad(angle)) * BALL_SPEED, sin(glm_rad(angle)) * BALL_SPEED}

typedef struct {
  Sprite base;
  int inBounds;
} Ball;

void ballMove(Ball *ball, Paddle paddles[]);

#endif
