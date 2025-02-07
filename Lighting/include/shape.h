#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include "shader.h"
#include "texture.h"

#define PI GLM_PI

typedef enum { VERTICES, TEXTURE, NORMALS } VBOAttribs;

typedef struct {
  /*** OPENGL DATA ***/
  GLuint VAO;
  GLuint EBO;
  GLuint VBO[3];
  Shader *shader;
  Texture *texture;
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
  unsigned *indices;
  /*** TRANSFORM DATA ***/
  vec3 position;
  vec3 rotation;
  vec3 size;
  vec3 color;
} Shape;

void shapeSetData(Shape *shape);
void shapeDraw(Shape shape, mat4 model);
void shapeTranslate(Shape shape, float *pos, float *rot, float *size, vec4 *model);
void shapeDelete(Shape *shape);

#endif
