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
  unsigned numVerts = 0, numTex = 0, numNormals = 0;
  unsigned indexV, indexVT, indexVN;
  size_t vBytes = 10, vtBytes = 10, vnBytes = 10;
  size_t model_vBytes = 10, model_vtBytes = 10, model_vnBytes = 10;
  /*float *vertValues, *texValues, *normalValues;*/
  vec3 *vertValues, *texValues, *normalValues;
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

  model.vertices = calloc(model_vBytes, sizeof(float));
  model.normals = calloc(model_vnBytes, sizeof(float));
  model.textureCoords = calloc(model_vtBytes, sizeof(float));
  vertValues = calloc(vBytes, sizeof(vec3));
  normalValues = calloc(vnBytes, sizeof(vec3));
  texValues = calloc(vtBytes, sizeof(vec3));

  while (fgets(line, BUF_SIZE, src)) {
    // Vertex Values
    if (line[0] == 'v' && line[1] == ' ') {
      // Realloc
      if (numVerts + 3 > vBytes)
        vertValues = realloc(vertValues, (vBytes *= 2) * sizeof(vec3));
      sscanf(line, "v %f %f %f\n", &x, &y, &z);
      vertValues[numVerts][0] = x;
      vertValues[numVerts][1] = y;
      vertValues[numVerts][2] = z;
      numVerts++;
    }

    // Normal Values
    if (line[0] == 'v' && line[1] == 'n') {
      // Realloc
      if (numNormals + 3 > vnBytes)
        normalValues = realloc(normalValues, (vnBytes *= 2) * sizeof(vec3));
      sscanf(line, "vn %f %f %f\n", &x, &y, &z);
      normalValues[numNormals][0] = x;
      normalValues[numNormals][1] = y;
      normalValues[numNormals][2] = z;
      numNormals++;
    }

    // Texture Values
    if (line[0] == 'v' && line[1] == 't') {
      // Realloc
      if (numTex + 2 > vtBytes)
        texValues = realloc(texValues, (vtBytes *= 2) * sizeof(vec3));
      sscanf(line, "vt %f %f\n", &x, &y);
      texValues[numTex][0] = x;
      texValues[numTex][1] = y;
      numTex++;
    }

    // Indices
    /*model.textureCoords = calloc(vtBytes, sizeof(float));*/
    /*model.normals = calloc(vnBytes, sizeof(float));*/
    if (line[0] == 'f' && line[1] == ' ') {
      int j = 0;
      for (linePtr = &line[2]; linePtr < line + strlen(line); linePtr++) {
        if (*linePtr == ' ' || *linePtr == '\n') {
          if (model.numVertices + 3 > model_vBytes)
            model.vertices = realloc(model.vertices, (model_vBytes *= 2) * sizeof(float));
          if (model.numNormals + 3 > model_vnBytes)
            model.normals = realloc(model.normals, (model_vnBytes *= 2) * sizeof(float));
          if (model.numTextureCoords + 2 > model_vtBytes)
            model.textureCoords = realloc(model.textureCoords, (model_vtBytes *= 2) * sizeof(float));
          fieldBuffer[j] = '\0';
          sscanf(fieldBuffer, "%u/%u/%u", &indexV, &indexVT, &indexVN);
          model.vertices[model.numVertices++] = vertValues[indexV - 1][0];
          model.vertices[model.numVertices++] = vertValues[indexV - 1][1];
          model.vertices[model.numVertices++] = vertValues[indexV - 1][2];
          model.normals[model.numNormals++] = normalValues[indexVN - 1][0];
          model.normals[model.numNormals++] = normalValues[indexVN - 1][1];
          model.normals[model.numNormals++] = normalValues[indexVN - 1][2];
          model.textureCoords[model.numTextureCoords++] = texValues[indexVT - 1][0];
          model.textureCoords[model.numTextureCoords++] = texValues[indexVT - 1][1];
          j = 0;
        } else {
          fieldBuffer[j] = *linePtr;
          j++;
        }
      }
    }
  }

  // Reallocates each attribute to match the exact number of elements
  model.vertices = realloc(model.vertices, model.numVertices * sizeof(float));
  model.normals = realloc(model.normals, model.numNormals * sizeof(float));
  model.textureCoords = realloc(model.textureCoords, model.numTextureCoords * sizeof(float));
  
  model.shader = shader;
  model.texture = texture;

  setData(&model);

  return model;
}

void setData(Model *model) {
  printf("Setting Data\n");
  printf("Vertices: %lu\n", model->numVertices);
  glGenVertexArrays(1, &model->VAO);
  glBindVertexArray(model->VAO);

  glGenBuffers(3, model->VBO);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, model->VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, model->numVertices * sizeof(float), model->vertices, GL_STATIC_DRAW);

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
  glDrawArrays(GL_TRIANGLES, 0, model.numVertices);
  /*glDrawElements(GL_TRIANGLES, model.numIndices, GL_UNSIGNED_INT, (void *)0);*/

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
