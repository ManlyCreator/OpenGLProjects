#include "torus.h"
#include "shape.h"

Torus torusInit(int rings, int stacks, float insideRadius, float ringRadius, Shader *shader, Texture *texture) {
  Torus torus;

  float x, y, z;
  float xz;
  float nx, ny, nz;
  float s, t;
  float insideAngle, ringAngle;
  float v1, v2;
  float insideAngleStep = 2 * PI / rings;
  float ringAngleStep = 2 * PI / stacks;

  torus.numVertices = 0;
  torus.numTextureCoords = 0;
  torus.numNormals = 0;
  torus.numIndices = 0;

  torus.vertices = malloc((rings + 1) * (stacks + 1) * 3 * sizeof(float));
  torus.textureCoordinates = malloc((rings + 1) * (stacks + 1) * 2 * sizeof(float));
  torus.normals = malloc((rings + 1) * (stacks + 1) * 3 * sizeof(float));
  torus.indices = malloc(rings * stacks * 6 * sizeof(unsigned));

  for (int i = 0; i <= rings; i++) {
    insideAngle = i * insideAngleStep;

    for (int j = 0; j <= stacks; j++) {
      // Normals
      ringAngle = PI - j * ringAngleStep;

      x = (insideRadius * cos(insideAngle)) + (ringRadius * cos(ringAngle) * cos(insideAngle));
      y = sin(ringAngle);
      z = (insideRadius * sin(insideAngle)) + (ringRadius * cos(ringAngle) * sin(insideAngle));

      torus.vertices[torus.numVertices++] = x;
      torus.vertices[torus.numVertices++] = y;
      torus.vertices[torus.numVertices++] = z;

      // Texture Coordinates
      s = (float)i * 2.0f / rings;
      t = (float)j / stacks;
      torus.textureCoordinates[torus.numTextureCoords++] = s;
      torus.textureCoordinates[torus.numTextureCoords++] = t;
    }
  }

  for (int i = 0; i < rings; i++) {
    v1 = i * (stacks + 1); 
    v2 = v1 + stacks + 1;
    for (int j = 0; j < stacks; j++, v1++, v2++) {
      torus.indices[torus.numIndices++] = v1;
      torus.indices[torus.numIndices++] = v2;
      torus.indices[torus.numIndices++] = v1 + 1;

      torus.indices[torus.numIndices++] = v1 + 1;
      torus.indices[torus.numIndices++] = v2;
      torus.indices[torus.numIndices++] = v2 + 1;
    }
  }

  shapeSetData(&torus);

  torus.shader = shader;
  torus.texture = texture;

  return torus;
}
