#version 330 core

uniform sampler2D texture1;
uniform sampler2D texture2;

in float outAlpha;
in vec3 outCol;
in vec2 outTexCoord;

out vec4 fragCol;

void main() {
  fragCol = mix(texture(texture1, outTexCoord), texture(texture2, vec2(1.0f - outTexCoord.x, outTexCoord.y)), outAlpha) * vec4(outCol, 1.0f);
}
