#version 330 core

uniform mat4 projection;
uniform mat4 model;

layout (location = 0) in vec3 pos;

void main() {
  gl_Position = projection * model * vec4(pos, 1.0f);
}
