#include "scene.h"
#include <cglm/vec3.h>

Scene sceneInit(Shader shader) {
  Scene scene;
  float cube[] = {
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
  float pyramid[] = {
    // Front Face
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     0.0f,  1.0f,  0.0f,
    
    // Back Face
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     0.0f,  1.0f,  0.0f,

    // Left Face
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     0.0f,  1.0f,  0.0f,

    // Right Face
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     0.0f,  1.0f,  0.0f,

    // Base - Left
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,

    // Base - Right
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f
     
  };
  float bipyramid[] = {
    // Front Face - Top
    -1.0f,  0.0f,  1.0f,
     1.0f,  0.0f,  1.0f,
     0.0f,  1.5f,  0.0f,
    
    // Back Face - Top
    -1.0f,  0.0f, -1.0f,
     1.0f,  0.0f, -1.0f,
     0.0f,  1.5f,  0.0f,

    // Left Face - Top
    -1.0f,  0.0f,  1.0f,
    -1.0f,  0.0f, -1.0f,
     0.0f,  1.5f,  0.0f,

    // Right Face - Top
     1.0f,  0.0f,  1.0f,
     1.0f,  0.0f, -1.0f,
     0.0f,  1.5f,  0.0f,
    
    // Front Face - Bottom
    -1.0f,  0.0f,  1.0f,
     1.0f,  0.0f,  1.0f,
     0.0f, -1.5f,  0.0f,
    
    // Back Face - Bottom
    -1.0f,  0.0f, -1.0f,
     1.0f,  0.0f, -1.0f,
     0.0f, -1.5f,  0.0f,

    // Left Face - Bottom
    -1.0f,  0.0f,  1.0f,
    -1.0f,  0.0f, -1.0f,
     0.0f, -1.5f,  0.0f,

    // Right Face - Bottom
     1.0f,  0.0f,  1.0f,
     1.0f,  0.0f, -1.0f,
     0.0f, -1.5f,  0.0f,
  };

  glGenVertexArrays(1, &scene.VAO);
  glBindVertexArray(scene.VAO);

  glGenBuffers(3, scene.VBOs);
  // Cube Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[CUBE]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

  // Pyramid Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[PYRAMID]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

  // Bipyramid Vertex Buffer
  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[BIPYRAMID]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(bipyramid), bipyramid, GL_STATIC_DRAW);

  // Reset Buffers
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Assign Shader Program
  scene.shader = shader;

  return scene;
}

void cubeDraw(Scene scene) {
  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[CUBE]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void pyramidDraw(Scene scene) {
  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[PYRAMID]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 18);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void bipyramidDraw(Scene scene) {
  shaderUse(scene.shader);
  glBindVertexArray(scene.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, scene.VBOs[BIPYRAMID]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 24);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
