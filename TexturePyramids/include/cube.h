#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include "shader.h"

typedef struct {
  unsigned shader;
  unsigned VAO;
  vec3 position;
  vec3 size;
  vec3 rotation;
} Cube;

Cube cubeInit(Shader shader, vec3 pos, vec3 size, vec3 rot);
void cubeDraw(Cube cube, long number);
