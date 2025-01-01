#version 330 core

uniform float xOffset;
uniform float yOffset;
uniform float alpha;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 texCoord;

out float outAlpha;
out vec3 outCol;
out vec2 outTexCoord;

void main() {
  gl_Position = perspective * view * model * vec4(pos.x + xOffset, pos.y + yOffset, pos.z, 1.0f);
  outCol = col;
  outTexCoord = texCoord;
  outAlpha = alpha;
}
