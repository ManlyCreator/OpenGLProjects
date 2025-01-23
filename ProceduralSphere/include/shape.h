#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include "shader.h"
#include "texture.h"

#define PI GLM_PI

typedef struct {
  GLuint VAO;
  GLuint EBO;
  GLuint VBO[4];
  Shader shader;
  Texture texture;
  /*** VERTEX DATA ***/
  // Scalars
  long numVertices;
  long numTextureCoords;
  long numNormals;
  long numIndices;
  // Arrays
  float *vertices; 
  float *textureCoordinates;
  float *normals;
  int *indices;
  /*** TRANSFORM DATA ***/
  vec3 position;
  vec3 rotation;
  vec3 size;
} Shape;

void shapeSetData(Shape *shape);
void shapeDraw(Shape shape, mat4 model);
void shapeTranslate(Shape shape, float *pos, float *rot, float *size, vec4 *model);
void shapeDelete(Shape *shape);

#endif
