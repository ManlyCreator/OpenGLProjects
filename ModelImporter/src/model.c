#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

// TODO: Debug seg fault after parsing texture coordinates
// Send data to OpenGL
// Draw model

Model modelParse(const char *objFile) {
  Model model;
  char c;
  size_t vBytes = 10, vtBytes = 10, vnBytes = 10;
  char attribute[3];
  char values[LINE_LEN];
  char *linePtr, *currentChar;

  FILE *src = fopen(objFile, "r");

  if (!src) {
    printf("Failed to read OBJ file\n");
    exit(EXIT_FAILURE);
  }

  model.numVertices = 0;
  model.numTextureCoords = 0;
  model.numNormals = 0;

  model.vertices = malloc(vBytes * sizeof(float));
  model.textureCoords = malloc(vtBytes * sizeof(float));
  model.normals = malloc(vnBytes * sizeof(float));

  // Skips to the first attribute
  while((c = fgetc(src)) != 'v');
  ungetc(c, src);

  while (1) {
    // Reads to the first space to store the attribute type
    currentChar = attribute;
    while ((c = fgetc(src)) != ' ')
      *(currentChar++) = c;   
    *(currentChar) = '\0';

    // Breaks if an invalid line is read
    printf("Attribute: %s\n", attribute);
    if (strcmp(attribute, "v") && strcmp(attribute, "vt") && strcmp(attribute, "vn")) {
      printf("Breaking\n");
      break;
    }

    // Vertex Coordinates
    if (!strcmp(attribute, "v")) {
      // Realloc
      if (model.numVertices + 3 > vBytes) {
        model.vertices = realloc(model.vertices, (vBytes + 10) * sizeof(float));
        vBytes += 10;
      }
      fscanf(src, " %f", &model.vertices[model.numVertices++]);
      fscanf(src, " %f", &model.vertices[model.numVertices++]);
      fscanf(src, " %f\n", &model.vertices[model.numVertices++]);
      printf("v: < %f, %f, %f >\n", model.vertices[model.numVertices - 3], model.vertices[model.numVertices - 2], model.vertices[model.numVertices - 1]);
    }

    // Normals
    if (!strcmp(attribute, "vn")) {
      // Realloc
      if (model.numNormals + 3 > vnBytes) {
        model.normals = realloc(model.normals, (vtBytes + 10) * sizeof(float));
        vtBytes += 10;
      }
      fscanf(src, " %f", &model.normals[model.numNormals++]);
      fscanf(src, " %f", &model.normals[model.numNormals++]);
      fscanf(src, " %f\n", &model.normals[model.numNormals++]);
      printf("vn: < %f, %f, %f >\n", model.normals[model.numNormals - 3], model.normals[model.numNormals - 2], model.normals[model.numNormals - 1]);
    }

    // Texture Coordinates
    if (!strcmp(attribute, "vt")) {
      // Realloc
      if (model.numTextureCoords + 2 > vtBytes) {
        model.textureCoords = realloc(model.textureCoords, (vtBytes + 10) * sizeof(float));
        vtBytes += 10;
      }
      fscanf(src, " %f", &model.textureCoords[model.numTextureCoords++]);
      fscanf(src, " %f\n", &model.textureCoords[model.numTextureCoords++]);
      printf("vt: < %f, %f >\n", model.textureCoords[model.numTextureCoords - 2], model.textureCoords[model.numTextureCoords - 1]);
    }
  }

  return model;
}
