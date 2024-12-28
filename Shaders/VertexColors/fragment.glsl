#version 330 core
in vec3 fragColOut;
out vec4 col;
void main() {
  col = vec4(fragColOut, 1.0f);
}
