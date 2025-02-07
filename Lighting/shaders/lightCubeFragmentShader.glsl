#version 420 core

uniform vec3 objectColor;

out vec4 fragCol;

void main(void) {
  fragCol = vec4(objectColor, 1.0f);
}
