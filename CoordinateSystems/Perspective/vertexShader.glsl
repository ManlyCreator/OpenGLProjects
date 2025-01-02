#version 330 core

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 outTexCoord;

void main() {
  gl_Position = perspective * view * model * vec4(pos, 1.0f);
  outTexCoord = texCoord;
}
