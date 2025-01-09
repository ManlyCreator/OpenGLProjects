#include "ball.h"
#include "sprite.h"

// TODO: Calculate center of the ball & paddle. Find the closest point from these points, and use that as the hit position.
void ballMove(Ball *ball, Paddle paddles[]) {
  vec2 compass[] = {
    {0.0f, 1.0f},  // Up
    {0.0f, -1.0f}, // Down
    {1.0f, 0.0f},  // Right
    {-1.0f, 0.0f}  // Left
  };
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
    paddle = paddles[i].base;
    if (ballSprite->position[0] <= paddle.position[0] + paddle.size[0] && ballSprite->position[0] + ballSprite->size[0] >= paddle.position[0] &&
        ballSprite->position[1] <= paddle.position[1] + paddle.size[1] && ballSprite->position[1] >= paddle.position[1]) {
      int direction = 0;
      float dot;
      float clampedX, clampedY;
      float penetration;
      float max = 0.0f;
      vec2 ballCenter, paddleCenter, paddleHalfExtents, hit, difference;
      glm_vec2((vec2){ballSprite->position[0] + ballSprite->size[0] / 2, ballSprite->position[1] + ballSprite->size[1] / 2}, ballCenter);
      glm_vec2((vec2){paddle.size[0] / 2, paddle.size[1] / 2}, paddleHalfExtents);
      glm_vec2((vec2){paddle.position[0] + paddleHalfExtents[0], paddle.position[1] + paddleHalfExtents[1]}, paddleCenter);
      glm_vec2_sub(ballCenter, paddleCenter, difference);
      clampedX = glm_clamp(difference[0], -paddleHalfExtents[0], paddleHalfExtents[0]); 
      clampedY = glm_clamp(difference[1], -paddleHalfExtents[1], paddleHalfExtents[1]); 
      glm_vec2((vec2){clampedX, clampedY}, difference);
      glm_vec2_add(paddleCenter, difference, hit);
      glm_vec2_sub(hit, ballCenter, difference);
      glm_vec2_normalize(difference);
      for (int i = 0; i < 4; i++) {
        dot = glm_vec2_dot(difference, compass[i]);
        // printf("Dot: %g\n", dot);
        if (dot > max) {
          max = dot;
          direction = i;
        }
      }
      // printf("Edge: %s\n", direction == UP || direction == DOWN ? "HORIZONTAL" : "VERTICAL");
      if (direction == UP || direction == DOWN) {
        if (fabs(paddle.velocity[1]) > 0) {
          ballSprite->velocity[1] = paddle.velocity[1];
        }
        else
          ballSprite->velocity[1] = -ballSprite->velocity[1];
        penetration = (ballSprite->size[1] / 2) - difference[1];
        if (direction == UP)
          ballSprite->position[1] -= penetration;
        else
          ballSprite->position[1] += penetration;
      }
      else {
        ballSprite->velocity[0] = -ballSprite->velocity[0];
        penetration = (ballSprite->size[0] / 2) - difference[0];
        if (direction == RIGHT)
          ballSprite->position[0] -= penetration;
        else
          ballSprite->position[0] += penetration;
      }
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
