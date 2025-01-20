#include "scene.h"
#include "shader.h"

Scene sceneInit(Shader shader) {
  Scene scene;
  float pyramid[] = {
    /* Vertices */ /* Texture */
    // Front Face
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     0.0f,  1.0f,  0.0f, 0.5f, 1.0f,

    // Back Face
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     0.0f,  1.0f,  0.0f, 0.5f, 1.0f,

    // Left Face
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     0.0f,  1.0f,  0.0f, 0.5f, 1.0f,

    // Right Face
     1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     0.0f,  1.0f,  0.0f, 0.5f, 1.0f,

    // Base
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
  };
  float cube[] = {
    /* Vertices */ /* Texture */
    // Front
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
    
    // Back
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

    // Right
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 1.0f,

    // Left
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

    // Top
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

    // Bottom
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
  };

  glGenVertexArrays(1, &scene.VAO);
  glBindVertexArray(scene.VAO);

  glGenBuffers(NUM_SHAPES, scene.VBOs);

  // Pyramid Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[PYRAMID]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.pyramid.position);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.pyramid.size);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.pyramid.rotation);

  // Cube Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[CUBE]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.cube.position);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.cube.size);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, scene.cube.rotation);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  scene.shader = shader;

  return scene;
}

void sceneDraw(Scene scene, int shapeEnum) {
  int nVertices;
  mat4 model;
  Shape shape;

  switch (shapeEnum) {
    case (PYRAMID):
     shape = scene.pyramid; 
     nVertices = PYRAMID_VERTS;
     break;
    case (CUBE):
     shape = scene.cube; 
     nVertices = CUBE_VERTS;
     break;
  }

  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  // Transform
  glm_mat4_identity(model);
  glm_translate(model, shape.position);
  glm_rotate(model, glm_rad(shape.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(model, glm_rad(shape.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(model, glm_rad(shape.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});
  glm_scale(model, shape.size);

  shaderSetMatrix4(scene.shader, "model", model);
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[shapeEnum]);

  // Vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

  // Texture
  if (shape.texture) {
    shaderSetInt(scene.shader, "textureFlag", 1);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    textureUse(shape.texture);
  } else {
    shaderSetInt(scene.shader, "textureFlag", 0);
  }

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, nVertices);

  // Reset
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
