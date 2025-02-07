#include "torus.h"
#include "shape.h"

Torus torusInit(int rings, int stacks, float insideRadius, float ringRadius, vec3 color, Shader *shader, Texture *texture) {
  Torus torus;

  float x, y, z;
  float xz;
  float nx, ny, nz;
  float radiusInv = 1.0f / ringRadius;
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
      ringAngle = PI - j * ringAngleStep;

      // Normals
      xz = ringRadius * cos(ringAngle);
      x = xz * cos(insideAngle);
      y = sin(ringAngle);
      z = xz * sin(insideAngle);

      nx = x * radiusInv; 
      ny = y * radiusInv; 
      nz = z * radiusInv; 

      torus.normals[torus.numNormals++] = nx; 
      torus.normals[torus.numNormals++] = ny; 
      torus.normals[torus.numNormals++] = nz; 

      // Vertices
      x += insideRadius * cos(insideAngle);
      z += insideRadius * sin(insideAngle);

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

  glm_vec3_copy(color, torus.color);
  torus.shader = shader;
  torus.texture = texture;

  return torus;
}
