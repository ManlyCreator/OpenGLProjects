#include "ball.h"
#include "sprite.h"

void ballMove(Ball *ball, Paddle paddles[]) {
  Sprite *ballSprite = &ball->base;
  Sprite paddle;
  Sprite hitSprite;

  glm_vec2_add(ballSprite->position, ballSprite->velocity, ballSprite->position);

  // Screen Collision
  if (-(float)HEIGHT > ballSprite->position[1] || ballSprite->position[1] > (float)HEIGHT - ballSprite->size[1]) {
    ballSprite->velocity[1] = -ballSprite->velocity[1];
  }

  // Paddle Collision
  for (int i = 0; i < 2; i++) {
    int collision;
    paddle = paddles[i].base;
    collision = spriteCheckCollide(*ballSprite, paddle);

    if (collision) {
      float spriteRight = ballSprite->position[0] + ballSprite->size[0];
      float spriteTop = ballSprite->position[1] + ballSprite->size[1];
      float paddleRight = paddle.position[0] + paddle.size[0];
      float paddleTop = paddle.position[1] + paddle.size[1];

      float overlapRight = spriteRight - paddle.position[0];
      float overlapLeft = paddleRight - ballSprite->position[0];
      float overlapTop = spriteTop - paddle.position[1];
      float overlapBottom = paddleTop - ballSprite->position[1];

      float minOverlap = fminf(fminf(overlapRight, overlapLeft), fminf(overlapTop, overlapBottom));

      if (minOverlap == overlapRight || minOverlap == overlapLeft) {
        ballSprite->velocity[0] = -ballSprite->velocity[0];
        if (minOverlap == overlapRight)
          ballSprite->position[0] -= overlapRight;
        else
          ballSprite->position[0] += overlapLeft;
      }
      else {
        ballSprite->velocity[1] = -ballSprite->velocity[1];
        if (minOverlap == overlapTop) {
          ballSprite->position[1] += overlapTop;
        }
        else {
          ballSprite->position[1] += overlapBottom;
        }
      }
      if (sqrt(pow(ballSprite->velocity[0] * 1.1, 2) + pow(ballSprite->velocity[0] * 1.1, 2)) < 50) {
        ballSprite->velocity[0] *= 1.1;
        ballSprite->velocity[1] *= 1.1;
      }
    }
  }

  // Screen-Bounds Check
  if (-WIDTH > ballSprite->position[0] + ballSprite->size[0] || ballSprite->position[0] > WIDTH)
    ball->inBounds = 0;
  else
    ball->inBounds = 1;
}
