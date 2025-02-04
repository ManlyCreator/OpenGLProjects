#include "camera.h"

void updateVectors(Camera *camera);

Camera cameraInit(vec3 position, float pitch, float yaw) {
  Camera camera;

  glm_vec3_copy(position, camera.position);
  updateVectors(&camera);
  camera.pitch = pitch;
  camera.yaw = yaw;

  return camera;
}

void cameraProcessKeyboard(Camera *camera, CameraDirection direction) {
  vec3 dir;
  if (direction == FORWARD) {
    glm_vec3_scale(camera->front, CAMERA_SPEED, dir); 
    glm_vec3_add(camera->position, dir, camera->position);
  }
  if (direction == BACKWARD) {
    glm_vec3_scale(camera->front, CAMERA_SPEED, dir); 
    glm_vec3_sub(camera->position, dir, camera->position);
  }
  if (direction == RIGHT) {
    glm_vec3_cross(camera->front, WORLD_UP, dir);
    glm_vec3_normalize(dir);
    glm_vec3_scale(dir, CAMERA_SPEED, dir);
    glm_vec3_add(camera->position, dir, camera->position);
  }
  if (direction == LEFT) {
    glm_vec3_cross(camera->front, WORLD_UP, dir);
    glm_vec3_normalize(dir);
    glm_vec3_scale(dir, CAMERA_SPEED, dir);
    glm_vec3_sub(camera->position, dir, camera->position);
  }
}

void cameraProcessMouse(Camera *camera, float deltaX, float deltaY) {
  camera->pitch = glm_clamp(camera->pitch + (deltaY * CAMERA_SENSITIVITY), glm_rad(-89.9f), glm_rad(89.9f));
  camera->yaw += deltaX * CAMERA_SENSITIVITY;
  updateVectors(camera);
}

void cameraUpdateView(Camera *camera) {
  vec3 lookDir;
  mat4 lookAt;

  camera->front[0] = cos(camera->yaw) * cos(camera->pitch);
  camera->front[1] = sin(camera->pitch);
  camera->front[2] = sin(camera->yaw) * cos(camera->pitch);

  glm_mat4_identity(lookAt);
  glm_vec3_add(camera->position, camera->front, lookDir);
  glm_lookat(camera->position, lookDir, WORLD_UP, camera->view);
}

void updateVectors(Camera *camera) {
  // Calculate Right Vector
  glm_vec3_cross(camera->front, WORLD_UP, camera->right);
  glm_vec3_normalize(camera->right);

  // Calculate Up Vector
  glm_vec3_cross(camera->right, camera->front, camera->up);
  glm_vec3_normalize(camera->up);
}
