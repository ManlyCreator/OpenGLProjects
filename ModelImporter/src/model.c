#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

// First pass of parser totals up number of each attribute to be allocated
// TODO:
// Second pass stores each attribute in its respective buffer
// Send data to OpenGL
// Draw model

Model modelParse(const char *objFile) {
  Model model;
  unsigned long nV = 0, nVT = 0, nVN = 0;
  char line[LINE_LEN];
  char *linePtr, *currentChar;

  FILE *src = fopen(objFile, "r");

  if (!src) {
    printf("Failed to read OBJ file\n");
    exit(EXIT_FAILURE);
  }

  // First Pass
  while (fgets(line, LINE_LEN, src)) {
    linePtr = line;
    currentChar = linePtr;
    while (*(currentChar++) != ' ');
    *(currentChar - 1) = '\0';
    if (!strcmp(linePtr, "v"))
      nV++;
    else if (!strcmp(linePtr, "vt"))
      nVT++;
    else if (!strcmp(linePtr, "vn"))
      nVN++;
  }

  // Allocate Buffer Memory
  model.vertices = malloc(nV * sizeof(float));
  model.textureCoords = malloc(nVT * sizeof(float));
  model.normals = malloc(nVN * sizeof(float));

  // Reset File Ptr
  rewind(src);

  // Second Pass

  return model;
}
