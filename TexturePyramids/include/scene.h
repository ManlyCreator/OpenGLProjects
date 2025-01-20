#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include "texture.h"
#include "shader.h"

typedef enum { PYRAMID, CUBE } Shape; 

typedef struct {
  vec3 position;
  vec3 size;
  vec3 rotation;
} Plane;

typedef struct {
  Texture texture;
  vec3 position;
  vec3 size;
  vec3 rotation;
} Cube;

typedef struct {
  Texture texture;
  vec3 position;
  vec3 size;
  vec3 rotation;
} Pyramid;

typedef struct {
  Shader shader;
  unsigned VAO;
  unsigned VBOs[3];
  Cube cube;
  Pyramid pyramid;
} Scene;

Scene sceneInit(Shader shader);
void cubeDraw(Scene scene);
void pyramidDraw(Scene scene);

#endif
