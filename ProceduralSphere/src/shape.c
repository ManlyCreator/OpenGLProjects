#include "shape.h"

void shapeSetData(_Shape *shape) {
  GLuint VBOs[3];
  // VAO
  glGenVertexArrays(1, &shape->VAO);
  glBindVertexArray(shape->VAO);

  // VBOs
  glGenBuffers(3, VBOs);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  /*glBufferData(GL_ARRAY_BUFFER, sizeof(shape->vertices))*/
  
  // Texture
}

void shapeDraw(_Shape shape) {

}
