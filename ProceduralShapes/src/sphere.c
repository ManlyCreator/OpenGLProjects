#include "sphere.h"
#include "shape.h"

// TODO: Further understand sphere construction and then redo the class

Sphere sphereInit(int stackCount, int sectorCount, Shader shader, Texture texture) {
  Sphere sphere;
  int v1, v2;
  unsigned vertCount = sectorCount * stackCount;

  float x, y, z, xz;
  float s, t;

  float sectorAngle, stackAngle;
  float sectorStep = 2 * PI / sectorCount;
  float stackStep = PI / stackCount;

  sphere.numVertices = 0;
  sphere.numTextureCoords = 0;
  sphere.numNormals = 0;
  sphere.numIndices = 0;

  sphere.vertices = malloc((stackCount + 1) * (sectorCount + 1) * 3 * sizeof(float));
  sphere.textureCoordinates = malloc((stackCount + 1) * (sectorCount + 1) * 2 * sizeof(float));
  sphere.normals = malloc((stackCount + 1) * (sectorCount + 1) * 3 * sizeof(float));
  sphere.indices = malloc((stackCount * sectorCount * 6 - (sectorCount * 6)) * sizeof(unsigned));

  int vertCtr = 0;
  for (int i = 0; i <= stackCount; i++) {
    stackAngle = PI / 2 - i * stackStep;
    printf("Stack Angle: %f\n", glm_deg(stackAngle));
    xz = (float)cos(stackAngle); 

    for (int j = 0; j <= sectorCount; j++) {
      sectorAngle = j * sectorStep;

      // Vertex/Normal Positions
      x = (float)(xz * sin(sectorAngle));
      y = (float)(sin(stackAngle));
      z = (float)(xz * cos(sectorAngle)); 
      printf("[%d] x = %f\n", vertCtr, x);
      printf("[%d] y = %f\n", vertCtr, y);
      printf("[%d] z = %f\n", vertCtr, z);
      vertCtr++;

      // Texture Coordinates
      s = (float)j / sectorCount;
      t = (float)i / stackCount;

      // Vertices
      sphere.vertices[sphere.numVertices++] = x;
      sphere.vertices[sphere.numVertices++] = y;
      sphere.vertices[sphere.numVertices++] = z;

      // Texture
      sphere.textureCoordinates[sphere.numTextureCoords++] = s;
      sphere.textureCoordinates[sphere.numTextureCoords++] = t;

      // Normals
      sphere.normals[sphere.numNormals++] = x;
      sphere.normals[sphere.numNormals++] = y;
      sphere.normals[sphere.numNormals++] = z;
    }
  }

  int loopCtr = 0;
  for (int i = 0; i < stackCount; i++) {
    v1 = i * (sectorCount + 1);
    v2 = v1 + sectorCount + 1;
    printf("v1: %d\n", v1);
    printf("v2: %d\n", v2);

    for (int j = 0; j < sectorCount; j++, v1++, v2++) {
      if (i > 0) {
        sphere.indices[sphere.numIndices++] = v1;
        sphere.indices[sphere.numIndices++] = v2;
        sphere.indices[sphere.numIndices++] = v1 + 1;
      }

      if (i < stackCount - 1) {
        sphere.indices[sphere.numIndices++] = v1 + 1;
        sphere.indices[sphere.numIndices++] = v2;
        sphere.indices[sphere.numIndices++] = v2 + 1;
      }
    }
  }

  sphere.shader = shader;
  sphere.texture = texture;

  shapeSetData(&sphere);

  return sphere;
}
