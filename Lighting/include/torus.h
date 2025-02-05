#ifndef TORUS_H
#define TORUS_H

#include "shape.h"

typedef Shape Torus;

Torus torusInit(int rings, int stacks, float insideRadius, float ringRadius, vec3 color, Shader *shader, Texture *texture);

#endif
