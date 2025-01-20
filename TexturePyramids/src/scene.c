#include "scene.h"

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
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
  };

  float cube[] = {
    /* Vertices */ /* Texture */
    // Front
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
     1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f
    
    // Back
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,

    // Right
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,

    // Left
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,

    // Top
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f

    // Bottom
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f

  };

  glGenVertexArrays(1, &scene.VAO);
  glBindVertexArray(scene.VAO);

  glGenBuffers(2, scene.VBOs);

  // Pyramid Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[PYRAMID]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

  // Cube Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[CUBE]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  scene.shader = shader;

  return scene;
}

void cubeDraw(Scene scene) {
  mat4 model;

  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  glm_mat4_identity(model);
  glm_translate(model, scene.cube.position);
  glm_scale(model, scene.cube.size);
  glm_rotate(model, glm_rad(scene.cube.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(model, glm_rad(scene.cube.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(model, glm_rad(scene.cube.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});

  shaderSetMatrix4(scene.shader, "model", model);
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[CUBE]);

  // Vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

  // Texture
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void pyramidDraw(Scene scene) {
  mat4 model;

  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  // Transform
  glm_mat4_identity(model);
  glm_translate(model, scene.pyramid.position);
  glm_scale(model, scene.pyramid.size);
  glm_rotate(model, glm_rad(scene.pyramid.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(model, glm_rad(scene.pyramid.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(model, glm_rad(scene.pyramid.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});

  shaderSetMatrix4(scene.shader, "model", model);
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[PYRAMID]);

  // Vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

  // Texture
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  /*glActiveTexture(GL_TEXTURE0);*/
  /*glBindTexture(GL_TEXTURE_2D, scene.pyramid.texture);*/

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, 18);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
