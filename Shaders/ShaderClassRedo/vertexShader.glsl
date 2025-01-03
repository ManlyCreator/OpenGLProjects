#version 330 core

uniform float xOffset;
uniform float yOffset;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 outCol;

void main() {
  gl_Position = vec4(pos.x + xOffset, pos.y + yOffset, pos.z, 1.0f);
  outCol = col;
}
