#include "sphere.h"
#include "shape.h"

Sphere sphereInit(int precision) {
  Sphere sphere;
  float x, y, z;

  sphere.numVertices = (precision + 1) * (precision + 1);
  sphere.numIndices = precision * precision * 6;

  sphere.vertices = malloc(sphere.numVertices * sizeof(vec3));
  sphere.textureCoordinates = malloc(sphere.numVertices * sizeof(vec2));
  sphere.normals = malloc(sphere.numVertices * sizeof(vec3));
  sphere.indices = malloc(sphere.numIndices * sizeof(int));

  for (int i = 0; i <= precision; i++) {
    for (int j = 0; j <= precision; j++) {
      y = cos(glm_rad(180.0f - (float)i / precision));
      x = -cos(glm_rad(360.0f * j / precision)) * fabsf((float)cos(asin(y)));
      z = sin(glm_rad(360.0f * j / precision)) * fabsf((float)cos(asin(y)));
      // Vertices
      
      /*glm_vec3_copy((vec3){x, y, z}, sphere.vertices[i * (precision + 1) + j]);*/
      /*glm_vec2_copy((vec2){(float)j / precision, (float)i / precision}, sphere.textureCoordinates[i * (precision + 1) + j]);*/
      /*glm_vec3_copy((vec3){x, y, z}, sphere.normals[i * (precision + 1) + j]);*/
    }
  }

  for (int i = 0; i < precision; i++) {
    for (int j = 0; j < precision; j++) {
      sphere.indices[6 * (i * precision + j) + 0] = i * (precision + 1) + j;
      sphere.indices[6 * (i * precision + j) + 1] = i * (precision + 1) + j + 1;
      sphere.indices[6 * (i * precision + j) + 2] = (i + 1) * (precision + 1) + j;
      sphere.indices[6 * (i * precision + j) + 3] = i * (precision + 1) + j + 1;
      sphere.indices[6 * (i * precision + j) + 4] = (i + 1) * (precision + 1) + j + 1;
      sphere.indices[6 * (i * precision + j) + 5] = (i + 1) * (precision + 1) + j;
    }
  }

  // Sends data to OpenGL
  /*shapeSetData(&sphere);*/

  return sphere;
}
