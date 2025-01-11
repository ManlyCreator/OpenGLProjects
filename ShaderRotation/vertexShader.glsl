#version 330 core

const float PI = 3.14159265359;

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;
out vec3 outCol;

mat4 rotZ(float rad) {
  return mat4(cos(rad), sin(rad), 0.0f, 0.0f,
             -sin(rad), cos(rad), 0.0f, 0.0f,
              0.0f,     0.0f,     1.0f, 0.0f,
              0.0f,     0.0f,     0.0f, 1.0f);
              
}

void main() {
  mat4 rot = rotZ(PI / 2);
  gl_Position = rot * vec4(pos, 0.0f, 1.0f);
  outCol = col;
}
