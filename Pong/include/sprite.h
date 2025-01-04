#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include <cglm/cglm.h>

typedef struct {
  Shader shader;
  Texture texture;
  unsigned VAO;
} Sprite;

void spriteInit(Sprite *sprite);
void spriteDraw(Sprite sprite, vec2 pos, vec2 size, float rotate, vec3 color);

#endif
