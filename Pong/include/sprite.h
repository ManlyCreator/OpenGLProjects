#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include "game.h"
#include <cglm/cglm.h>

typedef struct {
  vec2 size;
  vec2 position;
  vec2 velocity;
  Shader shader;
  Texture texture;
  unsigned VAO;
} Sprite;

void spriteConstruct(Sprite *sprite, Shader shader, Texture texture, vec2 size, vec2 pos, vec2 velocity);
void spriteDraw(Sprite sprite, float rotate, vec3 color);
void spriteMove(Sprite *sprite);

#endif
