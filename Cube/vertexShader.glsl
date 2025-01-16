#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 pos;

out vec4 outCol;

void main(void) {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  outCol = vec4(pos, 1.0f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 1.0f);
}
