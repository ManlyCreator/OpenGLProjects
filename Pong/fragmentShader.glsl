#version 330 core

uniform int textureFlag;
uniform sampler2D textureSample;
uniform vec3 color;

in vec2 outTexCoords;
in vec3 outColor;

out vec4 col;

void main() {
  if (textureFlag == 1) {
    col = vec4(color, 1.0f) * texture(textureSample, outTexCoords);
  } else {
    col = vec4(color, 1.0f);
  }
}
