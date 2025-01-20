#version 420 core

layout (binding = 0) uniform sampler2D texSample;

in vec4 outCol;
in vec2 texCoords;

out vec4 fragCol;

void main(void) {
  fragCol = texture(texSample, texCoords) * outCol;
}
