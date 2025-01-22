#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include "shader.h"
#include "texture.h"

typedef struct {
  GLuint VAO;
  Shader shader;
  Texture texture;
  /*** VERTEX DATA ***/
  // Scalars
  int numVertices;
  int numIndices;
  // Arrays
  float *vertices; 
  float *textureCoordinates;
  float *normals;
  int *indices;
  /*** TRANSFORM DATA ***/
  vec3 position;
  vec3 rotation;
  vec3 size;
} _Shape;

void shapeSetData(_Shape *shape);
void shapeDraw(_Shape shape);

#endif
