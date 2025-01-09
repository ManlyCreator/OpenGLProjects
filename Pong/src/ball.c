#include "ball.h"
#include "sprite.h"

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
    int direction = 0;
    float dot;
    float length;
    float clampedX, clampedY;
    float penetration;
    float max = 0.0f;
    Collision collision;

    paddle = paddles[i].base;
    collision = spriteCheckCollide(*ballSprite, paddle);

    if (collision.didCollide) {
      glm_vec2_normalize(collision.difference);
      for (int i = 0; i < 4; i++) {
        dot = glm_vec2_dot(collision.difference, compass[i]);
        if (dot > max) {
          max = dot;
          direction = i;
        }
      }

      if (direction == UP || direction == DOWN) {
        if (fabs(paddle.velocity[1]) > 0)
          ballSprite->velocity[1] = paddle.velocity[1];
        else
          ballSprite->velocity[1] = -ballSprite->velocity[1];

        penetration = (ballSprite->size[1] / 2) - collision.difference[1];

        if (direction == UP)
          ballSprite->position[1] -= penetration;
        else
          ballSprite->position[1] += penetration;
      }
      else {
        ballSprite->velocity[0] = -ballSprite->velocity[0];

        penetration = (ballSprite->size[0] / 2) - collision.difference[0];

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
