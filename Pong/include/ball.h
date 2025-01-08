#ifndef BALL_H
#define BALL_H

#include "sprite.h"
#include "paddle.h"

#define BALL_WIDTH 20
#define BALL_SIZE (vec2){BALL_WIDTH, BALL_WIDTH}
#define BALL_POS (vec2){-(float)BALL_WIDTH / 2, -(float)BALL_WIDTH / 2}
#define BALL_ANGLE 110.0f
#define BALL_SPEED 10
#define BALL_VELOCITY (vec2){cos(glm_rad(BALL_ANGLE)) * BALL_SPEED, sin(glm_rad(BALL_ANGLE)) * BALL_SPEED}

typedef struct {
  Sprite base;
  int inBounds;
} Ball;

void ballMove(Ball *ball, Paddle paddles[]);

#endif
