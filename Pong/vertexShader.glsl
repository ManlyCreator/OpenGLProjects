#version 330 core

uniform mat4 projection;
uniform mat4 model;

layout (location = 0) in vec4 vertex;

out vec2 outTexCoords;

void main() {
  gl_Position = model * vec4(vertex.xy, 0.0f, 1.0f);
  outTexCoords = vertex.zw;
}
