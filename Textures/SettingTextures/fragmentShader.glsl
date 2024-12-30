#version 330 core

uniform sampler2D textureSample;

in vec3 outCol;
in vec2 outTexCoord;

out vec4 fragCol;

void main() {
  fragCol = texture(textureSample, outTexCoord) * vec4(outCol, 1.0f);
}
