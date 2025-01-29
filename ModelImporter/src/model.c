#include <stdio.h>
#include <stdlib.h>
#include "model.h"

Model modelParse(const char *objFile) {
  Model model;

  FILE *src = fopen(objFile, "r");

  if (!src) {
    printf("Failed to read OBJ file\n");
    exit(EXIT_FAILURE);
  }

  return model;
}
