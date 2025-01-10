#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include "game.h"
#include <cglm/cglm.h>

typedef enum {
  UP,
  DOWN,
  RIGHT,
  LEFT
} Direction;

typedef struct {
  vec2 size;
  vec2 position;
  vec2 velocity;
  Shader shader;
  Texture texture;
  unsigned VAO;
} Sprite;

typedef struct {
  int didCollide;
  vec2 difference;
} Collision;

void spriteConstruct(Sprite *sprite, Shader shader, Texture texture, vec2 size, vec2 pos, vec2 velocity);
void spriteDraw(Sprite sprite, float rotate, vec3 color);
int spriteCheckCollide(Sprite sprite1, Sprite sprite2);

#endif
