#version 330 core

uniform sampler2D textureSample;

in vec2 outTexCoords;

out vec4 col;

void main() {
  col = texture(textureSample, outTexCoords);
}
