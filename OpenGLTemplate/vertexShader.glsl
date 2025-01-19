#version 330 core

mat4 xRot(float rad);
mat4 yRot(float rad);
mat4 zRot(float rad);
mat4 translate(float x, float y, float z);

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float currentTime;

layout (location = 0) in vec3 pos;

out vec4 outCol;

void main(void) {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  outCol = vec4(pos, 1.0f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 1.0f);
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
