#include "sprite.h"
#include "shader.h"
#include "texture.h"

void spriteInit(Sprite *sprite) {
  float vertices[] = {
    // Vertices     // Texutre Coords
    -0.01f, -0.01f, 0.0f, 0.0f,
     0.01f, -0.01f, 1.0f, 0.0f,
     0.01f,  0.01f, 1.0f, 1.0f,
    -0.01f,  0.01f, 0.0f, 1.0f
  };
}

void spriteDraw(Sprite sprite, vec2 pos, vec2 size, float rotate, vec3 color) {
  mat4 model;

  shaderUse(sprite.shader);

  // Transformations
  glm_mat4_identity(model);
  glm_translate(model, (vec3){pos[0], pos[1]});
  glm_translate(model, (vec3){0.5 * size[0], 0.5 * size[1]});
  glm_rotate(model, glm_rad(rotate), (vec3){0.0f, 0.0f, 1.0f});
  glm_translate(model, (vec3){-0.5 * size[0], -0.5 * size[1]});
  glm_scale(model, (vec3){size[0], size[1]});

  shaderSetMatrix4(sprite.shader, "model", model);

  textureBind(sprite.texture);
}
