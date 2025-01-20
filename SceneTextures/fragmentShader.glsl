#version 420 core

layout (binding = 0) uniform sampler2D texSample;
uniform int textureFlag;

in vec4 outCol;
in vec2 texCoords;

out vec4 fragCol;

void main(void) {
  if (textureFlag != 0) {
    fragCol = texture(texSample, texCoords * 2);
  } else {
    fragCol = outCol;
  }
}
