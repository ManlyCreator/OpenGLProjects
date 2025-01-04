#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>

#include <glad/glad.h>

typedef unsigned Texture;

int textureConstruct(Texture *texture, const char *src);
void textureBind(Texture texture);

#endif
