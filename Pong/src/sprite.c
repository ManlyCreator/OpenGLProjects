#include "sprite.h"

void spriteConstruct(Sprite *sprite, Shader shader, Texture texture, vec2 size, vec2 pos, vec2 velocity) {
  unsigned VBO;

  // Set Attributes
  sprite->shader = shader;
  sprite->texture = texture;
  glm_vec2_copy(size, sprite->size);
  glm_vec2_copy(pos, sprite->position);
  glm_vec2_copy(velocity, sprite->velocity);

  float vertices[] = {
    // Vertices // Texture Coordinates
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  // Vertex Array
  glGenVertexArrays(1, &sprite->VAO);
  glBindVertexArray(sprite->VAO);

  // Vertex Buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void spriteDraw(Sprite sprite, float rotate, vec3 color) {
  mat4 model;

  // Shader
  shaderUse(sprite.shader);

  // Transformations
  glm_mat4_identity(model);
  glm_translate(model, (vec3){sprite.position[0], sprite.position[1]});
  glm_translate(model, (vec3){0.5 * sprite.size[0], 0.5 * sprite.size[1]});
  glm_rotate(model, glm_rad(rotate), (vec3){0.0f, 0.0f, 1.0f});
  glm_translate(model, (vec3){-0.5 * sprite.size[0], -0.5 * sprite.size[1]});
  glm_scale(model, (vec3){sprite.size[0], sprite.size[1]});

  shaderSetVector3f(sprite.shader, "color", color);
  shaderSetMatrix4(sprite.shader, "model", model);

  // Texture
  if (sprite.texture) {
    shaderSetInt(sprite.shader, "textureFlag", 1);
    textureBind(sprite.texture);
  } else
    shaderSetInt(sprite.shader, "textureFlag", 0);

  // Draw
  glBindVertexArray(sprite.VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void spriteMove(Sprite *sprite) {
  glm_vec2_add(sprite->position, sprite->velocity, sprite->position);
  if (-(float)HEIGHT > sprite->position[1] || sprite->position[1] > (float)HEIGHT - sprite->size[1])
    sprite->velocity[1] = -sprite->velocity[1];
}
