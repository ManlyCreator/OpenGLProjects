#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float currentTime;

layout (location = 0) in vec3 pos;

out vec4 outCol;

mat4 xRot(float rad);
mat4 yRot(float rad);
mat4 zRot(float rad);
mat4 translate(float x, float y, float z);

void main(void) {
  float timeFactor = currentTime + gl_InstanceID;
  float x = sin(timeFactor*5.2)*10.0f;
  float y = sin(timeFactor*5.4)*10.0f;
  float z = sin(timeFactor*5.6)*10.0f;
  mat4 rotationMatrix = xRot(timeFactor) * yRot(timeFactor) * zRot(timeFactor);
  mat4 newModel = translate(x, y, x) * rotationMatrix;
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
