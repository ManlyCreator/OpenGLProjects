#include "cube.h"
#include "shape.h"
#include <string.h>

Cube cubeInit(Shader shader, Texture texture) {
  Cube cube;
  float vertices[] = {
    // Front
    -1.0f, -1.0f, 1.0f,  
     1.0f, -1.0f, 1.0f,  
     1.0f,  1.0f, 1.0f,  
    -1.0f, -1.0f, 1.0f,  
     1.0f,  1.0f, 1.0f,  
    -1.0f,  1.0f, 1.0f,  
    
    // Back
    -1.0f, -1.0f, -1.0f, 
     1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Right
     1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
     1.0f, -1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
     1.0f,  1.0f,  1.0f, 

    // Left
    -1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f,  1.0f, 
    -1.0f,  1.0f,  1.0f, 
    -1.0f, -1.0f, -1.0f, 
    -1.0f,  1.0f,  1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Top
    -1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Bottom
    -1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f, 
  };
  float textureCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,  
    1.0f, 1.0f,
    0.0f, 0.0f,  
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
  };

  cube.shader = shader;
  cube.texture = texture;

  cube.numVertices = sizeof(vertices) / sizeof(vertices[0]);
  cube.numTextureCoords = sizeof(textureCoords) / sizeof(textureCoords[0]);
  cube.numNormals = 0;
  cube.numIndices = 0;

  cube.vertices = malloc(sizeof(vertices));
  cube.textureCoordinates = malloc(sizeof(textureCoords));
  cube.normals = NULL;
  cube.indices = NULL;
  memcpy(cube.vertices, vertices, sizeof(vertices));
  memcpy(cube.textureCoordinates, textureCoords, sizeof(textureCoords));

  shapeSetData(&cube);

  return cube;
}
