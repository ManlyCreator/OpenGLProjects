#version 330 core

in vec4 outCol;

out vec4 fragCol;

void main(void) {
  fragCol = outCol;
}
