#ifndef MODEL_H
#define MODEL_H

#define BUF_SIZE 256

#include "shader.h"
#include "texture.h"
#include <glad/glad.h>

typedef struct {
  GLuint VAO;
  GLuint VBO[3];
  GLuint *shader;
  GLuint *texture;
  unsigned long numVertices;
  unsigned long numTextureCoords;
  unsigned long numNormals;
  float *vertices;
  float *textureCoords;
  float *normals;
} Model;

// Stores model data in Model struct
Model modelInit(const char *objFile, Shader *shader, Texture *texture);
// Draws the model
void modelDraw(Model model, mat4 transform);

#endif

