#version 420 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 pos;

void main(void) {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
}
