#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

typedef Shape Cube;

Cube cubeInit(vec3 color, Shader *shader, Texture *texture);

#endif
