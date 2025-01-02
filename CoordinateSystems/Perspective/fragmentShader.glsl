#version 330 core

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 outTexCoord;

out vec4 fragCol;

void main() {
  fragCol = mix(texture(texture1, outTexCoord), texture(texture2, outTexCoord), 0.2f);
}
