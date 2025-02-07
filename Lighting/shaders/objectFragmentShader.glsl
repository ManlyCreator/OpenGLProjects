#version 420 core

layout (binding = 0) uniform sampler2D texSample;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform int textureFlag;

in vec4 outCol;
in vec2 texCoords;
in vec3 fragPos;
in vec3 normalFragPos;

out vec4 fragCol;

void main(void) {
  // Ambient
  float ambientStrength = 0.5f;
  vec3 ambientLight = lightColor * ambientStrength;

  // Diffuse
  vec3 norm = normalize(normalFragPos);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diffuseStrength = max(dot(norm, lightDir), 0.0f);
  vec3 diffuseLight = diffuseStrength * lightColor;

  vec3 finalLight = (ambientLight + diffuseLight) * objectColor;

  if (textureFlag != 0) {
    fragCol = texture(texSample, texCoords);
  } else {
    fragCol = vec4(finalLight, 1.0f);
  }
}
