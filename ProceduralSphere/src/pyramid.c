#include "pyramid.h"
#include "shape.h"
#include <string.h>

Pyramid pyramidInit(Shader shader, Texture texture) {
  Pyramid pyramid;
  float vertices[] = {
    // Front Face
    -1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f,  1.0f, 
     0.0f,  1.0f,  0.0f, 

    // Back Face
     1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f, 
     0.0f,  1.0f,  0.0f, 

    // Left Face
    -1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f,  1.0f, 
     0.0f,  1.0f,  0.0f, 

    // Right Face
     1.0f, -1.0f, -1.0f, 
     1.0f, -1.0f,  1.0f, 
     0.0f,  1.0f,  0.0f, 

    // Base
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
    0.5f, 1.0f,
               
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.5f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,  
    0.0f, 1.0f,  
  };
  pyramid.shader = shader;
  pyramid.texture = texture;

  pyramid.numVertices = sizeof(vertices) / sizeof(vertices[0]);
  pyramid.numTextureCoords = sizeof(textureCoords) / sizeof(textureCoords[0]);
  pyramid.numNormals = 0;
  pyramid.numIndices = 0;

  pyramid.vertices = malloc(sizeof(vertices));
  pyramid.textureCoordinates = malloc(sizeof(textureCoords));
  memcpy(pyramid.vertices, vertices, sizeof(vertices));
  memcpy(pyramid.textureCoordinates, textureCoords, sizeof(textureCoords));

  shapeSetData(&pyramid);

  return pyramid;
}
