#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 fragColIn;
out vec4 fragColOut;
uniform float xOffset;
void main() {
  gl_Position = vec4(pos.x + xOffset, pos.y, pos.z, 1.0f);
  fragColOut = gl_Position;
}
