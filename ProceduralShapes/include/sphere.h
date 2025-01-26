#ifndef SPHERE_H
#define SPHERE_H

#include <cglm/cglm.h>
#include "shape.h"

typedef Shape Sphere;

Sphere sphereInit(int stackCount, int sectorCount, Shader *shader, Texture *texture);

#endif
