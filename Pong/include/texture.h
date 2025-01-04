#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef unsigned Texture;

int textureConstruct(Texture *texture);
void textureBind(Texture texture);

#endif
