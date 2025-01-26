#ifndef TORUS_H
#define TORUS_H

#include "shape.h"

typedef Shape Torus;

Torus torusInit(int rings, Shader shader, Texture texture);

#endif
