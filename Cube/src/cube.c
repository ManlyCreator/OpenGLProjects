#include "cube.h"
#include <cglm/vec3.h>

Cube cubeInit(Shader shader, vec3 pos, vec3 size, vec3 rot) {
  Cube cube;
  unsigned VBO;
  float vertices[] = {
    // Front
    -1.0f,  1.0f, 1.0f, 
    -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,
    -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, 1.0f,

    // Back
    -1.0f,  1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,

    // Right
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    // Left
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,

    // Top
    -1.0f, 1.0f,  1.0f,
     1.0f, 1.0f,  1.0f,
    -1.0f, 1.0f, -1.0f,
     1.0f, 1.0f,  1.0f,
    -1.0f, 1.0f, -1.0f,
     1.0f, 1.0f, -1.0f,

    // Bottom
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
  };

  glGenVertexArrays(1, &cube.VAO);
  glBindVertexArray(cube.VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  cube.shader = shader;
  glm_vec3_copy(pos, cube.position);
  glm_vec3_copy(size, cube.size);
  glm_vec3_copy(rot, cube.rotation);

  return cube;
}

void cubeDraw(Cube cube) {
  mat4 model;

  glm_mat4_identity(model);
  glm_translate(model, cube.position);
  glm_scale(model, cube.size);
  glm_rotate(model, glm_rad(cube.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(model, glm_rad(cube.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(model, glm_rad(cube.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});

  shaderUse(cube.shader);
  shaderSetMatrix4(cube.shader, "model", model);
  glBindVertexArray(cube.VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
