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
  glm_translate(model, (vec3){0.5 * sprite.size[0], 0.5 * sprite.size[1]});
  glm_translate(model, (vec3){sprite.position[0], sprite.position[1]});
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

Collision spriteCheckCollide(Sprite sprite1, Sprite sprite2) {
  float length;
  float clampedX, clampedY;
  vec2 sprite1Center, sprite2Center, sprite2HalfExtents, hit, difference;
  Collision collision;

  glm_vec2((vec2){sprite1.position[0] + sprite1.size[0] / 2, sprite1.position[1] + sprite1.size[1] / 2}, sprite1Center);
  glm_vec2((vec2){sprite2.size[0] / 2, sprite2.size[1] / 2}, sprite2HalfExtents);
  glm_vec2((vec2){sprite2.position[0] + sprite2HalfExtents[0], sprite2.position[1] + sprite2HalfExtents[1]}, sprite2Center);
  glm_vec2_sub(sprite1Center, sprite2Center, difference);

  clampedX = glm_clamp(difference[0], -sprite2HalfExtents[0], sprite2HalfExtents[0]); 
  clampedY = glm_clamp(difference[1], -sprite2HalfExtents[1], sprite2HalfExtents[1]); 

  glm_vec2((vec2){clampedX, clampedY}, difference);
  glm_vec2_add(sprite2Center, difference, hit);
  glm_vec2_sub(hit, sprite1Center, difference);

  length = sqrt(pow(difference[0], 2) + pow(difference[1], 2));

  collision.didCollide = length <= sprite1.size[0] / 2;
  glm_vec2(difference, collision.difference);

  return collision;
}
