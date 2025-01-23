#include "shape.h"
#include "shader.h"
#include "texture.h"

void shapeSetData(Shape *shape) {
  // VAO
  glGenVertexArrays(1, &shape->VAO);
  glBindVertexArray(shape->VAO);

  // VBOs
  glGenBuffers(3, shape->VBO);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, shape->VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, shape->numVertices * sizeof(float), shape->vertices, GL_STATIC_DRAW);
  
  // Texture
  glBindBuffer(GL_ARRAY_BUFFER, shape->VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, shape->numTextureCoords * sizeof(float), shape->textureCoordinates, GL_STATIC_DRAW);

  // Normals
  if (shape->numNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, shape->VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, shape->numNormals * sizeof(float), shape->normals, GL_STATIC_DRAW);
  }

  // Indices
  if (shape->numIndices) {
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->numIndices * sizeof(unsigned), shape->indices, GL_STATIC_DRAW);
  }

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Set Transforms
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape->position);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape->rotation);
  glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, shape->size);
}

void shapeDraw(Shape shape, mat4 model) {
  shaderUse(shape.shader);
  glBindVertexArray(shape.VAO);

  // Transform
  shaderSetMatrix4(shape.shader, "model", model);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, shape.VBO[0]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // Texture
  glBindBuffer(GL_ARRAY_BUFFER, shape.VBO[1]);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

  if (shape.texture) {
    shaderSetInt(shape.shader, "textureFlag", 1);
    textureUse(shape.texture);
  } else {
    shaderSetInt(shape.shader, "textureFlag", 0);
  }

  // Draw
  if (shape.numIndices)
    glDrawElements(GL_TRIANGLES, shape.numIndices, GL_UNSIGNED_INT, (void*)0);
  else
    glDrawArrays(GL_TRIANGLES, 0, shape.numVertices);

  // Set Transform Data
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape.position);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape.rotation);
  glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, shape.size);

  // Reset
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void shapeTranslate(Shape shape, float *pos, float *rot, float *size, vec4 *model) {
  glm_mat4_identity(model);
  if (pos)
    glm_translate(model, pos);
  if (rot) {
    glm_rotate(model, glm_rad(rot[0]), (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(model, glm_rad(rot[1]), (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(model, glm_rad(rot[2]), (vec3){0.0f, 0.0f, 1.0f});
  }
  if (size)
    glm_scale(model, size);
}
