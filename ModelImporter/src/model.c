#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "shader.h"
#include "shape.h"
#include "texture.h"

void setData(Model *model);

// TODO: Create separate arrays to store read attributes
// TODO: Index temp arrays using the f attribute to store them in their respective struct array

Model modelInit(const char *objFile, Shader *shader, Texture *texture) {
  Model model;
  float x, y, z;
  unsigned indexV, indexVT, indexVN;
  size_t vBytes = 10, vtBytes = 10, vnBytes = 10, fBytes = 10;
  char line[BUF_SIZE];
  char fieldBuffer[BUF_SIZE];
  char *linePtr;

  // File Handling
  FILE *src = fopen(objFile, "r");

  if (!src) {
    printf("Failed to read OBJ file\n");
    exit(EXIT_FAILURE);
  }

  // Sets Initial Model Data
  model.numVertices = 0;
  model.numTextureCoords = 0;
  model.numNormals = 0;
  model.numIndices = 0;

  model.vertices = calloc(vBytes, sizeof(float));
  model.textureCoords = calloc(vtBytes, sizeof(float));
  model.normals = calloc(vnBytes, sizeof(float));
  model.indices = calloc(fBytes, sizeof(unsigned));

  while (fgets(line, BUF_SIZE, src)) {
    // Vertices
    if (line[0] == 'v' && line[1] == ' ') {
      // Realloc
      if (model.numVertices + 3 > vBytes)
        model.vertices = realloc(model.vertices, (vBytes *= 2) * sizeof(float));
      sscanf(line, "v %f %f %f\n", &x, &y, &z);
      model.vertices[model.numVertices++] = x;
      model.vertices[model.numVertices++] = y;
      model.vertices[model.numVertices++] = z;
    }

    // Indices
    if (line[0] == 'f' && line[1] == ' ') {
      if (model.numIndices + strlen(line) - 2 > fBytes)
        model.indices = realloc(model.indices, (fBytes *= 2) * sizeof(float));
      int j = 0;
      for (linePtr = &line[2]; linePtr < line + strlen(line); linePtr++) {
        if (*linePtr == ' ' || *linePtr == '\n') {
          fieldBuffer[j] = '\0';
          sscanf(fieldBuffer, "%u/%u/%u", &indexV, &indexVT, &indexVN);
          printf("%s\n", fieldBuffer);
          printf("Vertex Index: %u\n", indexV);
          model.indices[model.numIndices++] = indexV - 1;
          j = 0;
        } else {
          fieldBuffer[j] = *linePtr;
          j++;
        }
      }
    }
  }
  // File Reading Loop
  /*while (1) {*/
  /*  // Reads the line's attribute*/
  /*  readAttribute(attribute, src);*/
  /**/
  /*  // Breaks if an invalid line is read*/
  /*  if (strcmp(attribute, "v") && strcmp(attribute, "vt") && strcmp(attribute, "vn") && strcmp(attribute, "f")) */
  /*    break;*/
  /**/
  /*  // Vertex Coordinates*/
  /*  if (!strcmp(attribute, "v")) {*/
  /*    printf("Reading Vertex\n");*/
  /*    // Realloc*/
  /*    if (model.numVertices + 3 > vBytes)*/
  /*      model.vertices = realloc(model.vertices, (vBytes *= 2) * sizeof(float));*/
  /*    fscanf(src, " %f", &model.vertices[model.numVertices++]);*/
  /*    fscanf(src, " %f", &model.vertices[model.numVertices++]);*/
  /*    fscanf(src, " %f\n", &model.vertices[model.numVertices++]);*/
  /*  }*/
  /**/
  /*  // Normals*/
  /*  if (!strcmp(attribute, "vn")) {*/
  /*    printf("Reading Normal\n");*/
  /*    // Realloc*/
  /*    if (model.numNormals + 3 > vnBytes)*/
  /*      model.normals = realloc(model.normals, (vnBytes *= 2) * sizeof(float));*/
  /*    fscanf(src, " %f", &model.normals[model.numNormals++]);*/
  /*    fscanf(src, " %f", &model.normals[model.numNormals++]);*/
  /*    fscanf(src, " %f\n", &model.normals[model.numNormals++]);*/
  /*  }*/
  /**/
  /*  // Texture Coordinates*/
  /*  if (!strcmp(attribute, "vt")) {*/
  /*    printf("Reading Texture\n");*/
  /*    // Realloc*/
  /*    if (model.numTextureCoords + 2 > vtBytes)*/
  /*      model.textureCoords = realloc(model.textureCoords, (vtBytes *= 2) * sizeof(float));*/
  /*    fscanf(src, " %f", &model.textureCoords[model.numTextureCoords++]);*/
  /*    fscanf(src, " %f\n", &model.textureCoords[model.numTextureCoords++]);*/
  /*  }*/
  /**/
  /*  // Indices*/
  /*  if (!strcmp(attribute, "f")) {*/
  /*    printf("f %c\n", c = fgetc(src));*/
  /*    ungetc(c, src);*/
  /*  }*/
  /**/
  /*  // Breaks if the next character is EOF*/
  /*  /*printf("Next Character: %d\n", c = fgetc(src));*/
  /*  /*ungetc(c, src);*/
  /*  /*if ((c = fgetc(src)) == EOF)*/
  /*  /*  break;*/
  /*  /*ungetc(c, src);*/
  /*}*/

  // Reallocates each attribute to match the exact number of elements
  model.vertices = realloc(model.vertices, model.numVertices * sizeof(float));
  model.normals = realloc(model.normals, model.numNormals * sizeof(float));
  model.textureCoords = realloc(model.textureCoords, model.numTextureCoords * sizeof(float));
  model.indices = realloc(model.indices, model.numIndices * sizeof(unsigned));
  
  printf("Vertices: %lu\n", model.numVertices);

  model.shader = shader;
  model.texture = texture;

  setData(&model);

  return model;
}

void setData(Model *model) {
  glGenVertexArrays(1, &model->VAO);
  glBindVertexArray(model->VAO);

  glGenBuffers(3, model->VBO);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, model->VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, model->numVertices * sizeof(float), model->vertices, GL_STATIC_DRAW);

  // Indices
  glGenBuffers(1, &model->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->numIndices * sizeof(unsigned), model->indices, GL_STATIC_DRAW);

  // Texture
  if (model->numTextureCoords) {
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, model->numTextureCoords * sizeof(float), model->textureCoords, GL_STATIC_DRAW);
  }
  
  // Normals
  if (model->numNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, model->numNormals * sizeof(float), model->normals, GL_STATIC_DRAW);
  }

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void modelDraw(Model model, mat4 transform) {
  shaderUse(*model.shader);
  glBindVertexArray(model.VAO);

  // Transform
  shaderSetMatrix4(*model.shader, "model", transform);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, model.VBO[0]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);


  // Texture
  if (model.texture) {
    glBindBuffer(GL_ARRAY_BUFFER, model.VBO[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    shaderSetInt(*model.shader, "textureFlag", 1);
    textureUse(*model.texture);
  } else {
    shaderSetInt(*model.shader, "textureFlag", 0);
  }

  // Draw
  /*glDrawArrays(GL_TRIANGLES, 0, model.numVertices);*/
  glDrawElements(GL_TRIANGLES, model.numIndices, GL_UNSIGNED_INT, (void *)0);

  /*// Set Transform Data*/
  /*glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape.position);*/
  /*glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, shape.rotation);*/
  /*glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, shape.size);*/

  // Reset
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
