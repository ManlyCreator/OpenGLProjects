#ifndef MODEL_H
#define MODEL_H

#define LINE_LEN 100

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

