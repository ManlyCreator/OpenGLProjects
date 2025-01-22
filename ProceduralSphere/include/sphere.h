#ifndef SPHERE_H
#define SPHERE_H

#include <cglm/cglm.h>
#include "shape.h"

/*typedef struct {*/
/*  // Scalars*/
/*  int numVertices;*/
/*  int numIndices;*/
/*  // Arrays*/
/*  vec3 *vertices; */
/*  vec2 *textureCoordinates;*/
/*  vec3 *normals;*/
/*  int *indices;*/
/*} Sphere;*/

typedef _Shape Sphere;

Sphere sphereInit(int precision);

#endif
