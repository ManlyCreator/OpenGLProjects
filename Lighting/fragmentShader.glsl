#version 420 core

layout (binding = 0) uniform sampler2D texSample;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform int textureFlag;

in vec4 outCol;
in vec2 texCoords;

out vec4 fragCol;

void main(void) {
  if (textureFlag != 0) {
    fragCol = texture(texSample, texCoords);
  } else {
    fragCol = vec4(objectColor * lightColor, 1.0f);
  }
}
