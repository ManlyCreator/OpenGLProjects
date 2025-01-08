#include "ball.h"

void ballMove(Ball *ball, Paddle paddles[]) {
  vec2 compass[] = {
    {0.0f, 1.0f},  // Up
    {0.0f, -1.0f}, // Down
    {1.0f, 0.0f},  // Right
    {-1.0f, 0.0f}  // Left
  };
  Sprite *ballSprite = &ball->base;
  Sprite paddle;

  glm_vec2_add(ballSprite->position, ballSprite->velocity, ballSprite->position);

  // Screen Collision
  if (-(float)HEIGHT > ballSprite->position[1] || ballSprite->position[1] > (float)HEIGHT - ballSprite->size[1]) {
    ballSprite->velocity[1] = -ballSprite->velocity[1];
  }

  // Paddle Collision
  for (int i = 0; i < 2; i++) {
    paddle = paddles[i].base;
    // Vertical Edge Collision
    if (ballSprite->position[0] <= paddle.position[0] + paddle.size[0] && ballSprite->position[0] + ballSprite->size[0] >= paddle.position[0] &&
        ballSprite->position[1] <= paddle.position[1] + paddle.size[1] && ballSprite->position[1] >= paddle.position[1]) {
      vec2 paddleNormalized;
      float dot;
      glm_vec2_normalize_to(paddle.position, paddleNormalized);
      float max = 0.0f;
      int direction = 0;
      for (int i = 0; i < 4; i++) {
        dot = glm_vec2_dot(paddleNormalized, compass[i]);
        // printf("Dot: %g\n", dot);
        if (dot > max) {
          max = dot;
          direction = i;
        }
      }
      printf("Edge: %s\n", direction == 0 || direction == 1 ? "HORIZONTAL" : "VERTICAL");
      ballSprite->velocity[0] = -ballSprite->velocity[0];
      ballSprite->velocity[0] *= 1.1;
      ballSprite->velocity[1] *= 1.1;
    }
  }

  // Screen-Bounds Check
  if (-WIDTH > ballSprite->position[0] + ballSprite->size[0] || ballSprite->position[0] > WIDTH)
    ball->inBounds = 0;
  else
    ball->inBounds = 1;
}
