#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

typedef unsigned Texture;

Texture textureLoad(const char *src);
void textureUse(Texture texture);

#endif
