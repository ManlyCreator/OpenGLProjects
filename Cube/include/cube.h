#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include "shader.h"

typedef struct {
  unsigned VAO;
} Cube;

void cubeInit(Shader shader, vec3 pos, vec3 size);
void cubeDraw();
