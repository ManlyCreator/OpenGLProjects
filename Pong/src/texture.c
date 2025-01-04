#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int textureConstruct(Texture *texture, const char *src) {
  int width, height, nrChannels;
  unsigned char *textureData;

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

  stbi_set_flip_vertically_on_load(1);

  if (!(textureData = stbi_load(src, &width, &height, &nrChannels, 0))) {
    perror("Failed to load texture\n");
    return 0;
  }

  glActiveTexture(GL_TEXTURE0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  
  return 1;
}

void textureBind(Texture texture) {
  glBindTexture(GL_TEXTURE_2D, texture);
}
