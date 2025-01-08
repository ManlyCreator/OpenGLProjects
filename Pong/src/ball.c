#include "ball.h"

void ballMove(Ball *ball, Paddle paddles[]) {
  Sprite *ballSprite = &ball->base;
  Sprite paddle;
  glm_vec2_add(ballSprite->position, ballSprite->velocity, ballSprite->position);
  if (-(float)HEIGHT > ballSprite->position[1] || ballSprite->position[1] > (float)HEIGHT - ballSprite->size[1])
    ballSprite->velocity[1] = -ballSprite->velocity[1];
  for (int i = 0; i < 2; i++) {
    paddle = paddles[i].base;
    if (ballSprite->position[0] <= paddle.position[0] + paddle.size[0] && ballSprite->position[0] + ballSprite->size[0] >= paddle.position[0] &&
        ballSprite->position[1] <= paddle.position[1] + paddle.size[1] && ballSprite->position[1] >= paddle.position[1])
      ballSprite->velocity[0] = -ballSprite->velocity[0];
  }
  if (-WIDTH > ballSprite->position[0] || ballSprite->position[0] > WIDTH)
    ball->inBounds = 0;
  else
    ball->inBounds = 1;
}
