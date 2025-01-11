#include <cglm/cglm.h>
#include <stdio.h>
#include <math.h>

int main(void) {
  float angle;
  vec2 v1, v2;
  glm_vec2((vec2){1.0f, 0.0f}, v1);
  glm_vec2((vec2){0.0f, 1.0f}, v2);
  angle = acos(glm_vec2_dot(v1, v2));
  printf("Angle: %g\n", glm_deg(angle));
  printf("%g\n", glm_deg(0.12));
  return 0;
}
