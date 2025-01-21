#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include "texture.h"
#include "shader.h"

#define NUM_SHAPES 3
#define PYRAMID_VERTS 18
#define CUBE_VERTS 36

typedef enum { PYRAMID, CUBE } ShapeEnum; 

typedef struct {
  Texture texture;
  vec3 position;
  vec3 size;
  vec3 rotation;
} Shape;

typedef Shape Pyramid;
typedef Shape Cube;

typedef struct {
  Shader shader;
  unsigned VAO;
  unsigned VBOs[NUM_SHAPES];
  Pyramid pyramid;
  Cube cube;
} Scene;

Scene sceneInit(Shader shader);
void sceneDraw(Scene scene, int shapeEnum, mat4 model);
void sceneTranslate(Scene scene, vec3 pos, vec3 rot, vec3 size, mat4 model);

#endif
