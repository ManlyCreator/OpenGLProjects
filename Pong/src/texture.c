#include "texture.h"

int textureConstruct(Texture *texture) {
  glGenTextures(1, texture);
  return 1;
}
