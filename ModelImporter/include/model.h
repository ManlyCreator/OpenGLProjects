#ifndef MODEL_H
#define MODEL_H

typedef struct {
  unsigned long numVertices;
  unsigned long numTextureCoords;
  unsigned long numNormals;
  float *vertices;
  float *textureCoords;
  float *normals;

} Model;

Model modelParse(const char *objFile);

#endif

