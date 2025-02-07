#version 420 core

mat4 xRot(float rad);
mat4 yRot(float rad);
mat4 zRot(float rad);
mat4 translate(float x, float y, float z);

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float currentTime;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 normalPos;

out vec4 outCol;
out vec2 texCoords;
out vec3 fragPos;
out vec3 normalFragPos;

void main(void) {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  outCol = vec4(pos, 1.0f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 1.0f);
  texCoords = inTexCoords;
  fragPos = vec3(model * vec4(pos, 1.0f));
  normalFragPos = normalPos;
}

mat4 xRot(float rad) {
  mat4 rot = mat4(
    1.0f,  0.0f,     0.0f,     0.0f,
    0.0f,  cos(rad), sin(rad), 0.0f,
    0.0f, -sin(rad), cos(rad), 0.0f,
    0.0f,  0.0f,      0.0f,    1.0f 
  );
  return rot;
}

mat4 yRot(float rad) {
  mat4 rot = mat4(
    cos(rad), 0.0f, -sin(rad), 0.0f,
    0.0f,     1.0f,  0.0f,     0.0f,
    sin(rad), 0.0f, cos(rad),  0.0f,
    0.0f,     0.0f, 0.0f,      1.0f 
  );
  return rot;
}

mat4 zRot(float rad) {
  mat4 rot = mat4(
     cos(rad),  sin(rad), 0.0f, 0.0f,
    -sin(rad),  cos(rad), 0.0f, 0.0f,
     0.0f,      0.0f,     1.0f, 0.0f,     
     0.0f,      0.0f,     0.0f, 1.0f
  );
  return rot;
}

mat4 translate(float x, float y, float z) {
  mat4 translation = mat4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    x,    y,    z,    1.0f
  );
  return translation;
}
