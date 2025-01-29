#include "sphere.h"
#include "shape.h"

Sphere sphereInit(int stackCount, int sectorCount, Shader *shader, Texture *texture) {
  Sphere sphere;

  int s1, s2;

  float x, y, z, xz;
  float s, t;

  float sectorAngle, stackAngle;
  float sectorStep = PI * 2 / sectorCount;
  float stackStep = PI / stackCount;

  sphere.numVertices = 0;
  sphere.numTextureCoords = 0;
  sphere.numNormals = 0;
  sphere.numIndices = 0;

  sphere.vertices = malloc((sectorCount + 1) * (stackCount + 1) * 3 * sizeof(float));
  sphere.textureCoordinates = malloc((sectorCount + 1) * (stackCount + 1) * 2 * sizeof(float));
  sphere.normals = malloc((sectorCount + 1) * (stackCount + 1) * 3 * sizeof(float));
  sphere.indices = malloc((sectorCount * stackCount * 6 - (sectorCount * 6)) * sizeof(unsigned));

  // Map Out Vertices
  for (int i = 0; i <= stackCount; i++) {
    stackAngle = PI / 2 - i * stackStep;

    xz = cos(stackAngle);

    for (int j = 0; j <= sectorCount; j++) {
      sectorAngle = j * sectorStep;

      // Vertices/Normals
      x = xz * sin(sectorAngle);
      y = sin(stackAngle);
      z = xz * cos(sectorAngle);

      sphere.vertices[sphere.numVertices++] = x;
      sphere.vertices[sphere.numVertices++] = y;
      sphere.vertices[sphere.numVertices++] = z;

      sphere.normals[sphere.numNormals++] = x;
      sphere.normals[sphere.numNormals++] = y;
      sphere.normals[sphere.numNormals++] = z;

      // Texture Coordinates
      s = (float)j / sectorCount;
      t = (float)i / stackCount;

      sphere.textureCoordinates[sphere.numTextureCoords++] = s;
      sphere.textureCoordinates[sphere.numTextureCoords++] = t;
    }
  }

  // Map Out Indices
  for (int i = 0; i < stackCount; i++) {
    s1 = i * (sectorCount + 1);
    s2 = s1 + sectorCount + 1;

    /*printf("Stack %d\n", i);*/
    for (int j = 0; j < sectorCount; j++, s1++, s2++) {
      /*printf("  Sector %d\n", j);*/
      /*printf("%2d----%2d\n", s1, s1 + 1);*/
      /*printf(" |   / |\n");*/
      /*printf(" |  /  |\n");*/
      /*printf(" | /   |\n");*/
      /*printf("%2d----%2d\n", s2, s2 + 1);*/
      if (i > 0) {
        sphere.indices[sphere.numIndices++] = s1;
        sphere.indices[sphere.numIndices++] = s2;
        sphere.indices[sphere.numIndices++] = s1 + 1;
      }

      if (i < stackCount - 1) {
        sphere.indices[sphere.numIndices++] = s1 + 1;
        sphere.indices[sphere.numIndices++] = s2 + 1;
        sphere.indices[sphere.numIndices++] = s2;
      }
    }
  }

  // Texture & Shader
  sphere.shader = shader;
  sphere.texture = texture;

  // Send Data to OpenGL
  shapeSetData(&sphere);

  return sphere;
}
