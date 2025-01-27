#include "torus.h"
#include "shape.h"

Torus torusInit(int rings, Shader *shader, Texture *texture) {
  Torus torus;

  float x, y, z;
  float originX, originZ;
  float s, t;
  float hAngle, vAngle;
  float v1, v2;
  float angleStep = 2 * PI / rings;

  torus.numVertices = 0;
  torus.numTextureCoords = 0;
  torus.numNormals = 0;
  torus.indices = 0;

  torus.vertices = malloc((rings + 1) * (rings + 1) * 3 * sizeof(float));
  torus.textureCoordinates = malloc((rings + 1) * (rings + 1) * 2 * sizeof(float));
  torus.normals = malloc((rings + 1) * (rings + 1) * 3 * sizeof(float));
  torus.indices = malloc(rings * rings * 6 * sizeof(unsigned));

  for (int i = 0; i <= rings; i++) {
    hAngle = i * angleStep;
    originX = cos(hAngle) * 2.0f;
    originZ = sin(hAngle) * 2.0f;
    for (int j = 0; j <= rings; j++) {
      // Vertices
      vAngle = j * angleStep;

      x = cos(vAngle) + originX;
      y = sin(vAngle);
      z = originZ;

      torus.vertices[torus.numVertices++] = x;
      torus.vertices[torus.numVertices++] = y;
      torus.vertices[torus.numVertices++] = z;

      // Texture Coordinates
      s = (float)i / rings;
      t = (float)j / rings;
      torus.textureCoordinates[torus.numTextureCoords++] = s;
      torus.textureCoordinates[torus.numTextureCoords++] = t;
    }
  }

  for (int i = 0; i < rings; i++) {
    v1 = i * (rings + 1); 
    v2 = v1 + rings + 1;
    for (int j = 0; j < rings; j++, v1++, v2++) {
      torus.indices[torus.numIndices++] = v1;
      torus.indices[torus.numIndices++] = v2;
      torus.indices[torus.numIndices++] = v1 + 1;

      torus.indices[torus.numIndices++] = v1 + 1;
      torus.indices[torus.numIndices++] = v2;
      torus.indices[torus.numIndices++] = v2 + 1;
    }
  }

  printf("Setting Data\n");
  shapeSetData(&torus);
  printf("Set Data\n");

  torus.shader = shader;
  torus.texture = texture;
  printf("Set Shader & Texture\n");

  return torus;
}
