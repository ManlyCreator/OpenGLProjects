#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <cglm/cglm.h>

#define CAMERA_SPEED 0.5f
#define CAMERA_SENSITIVITY 0.01f
#define WORLD_UP (vec3){0.0f, 1.0f, 0.0f}

typedef enum { FORWARD, BACKWARD, RIGHT, LEFT } CameraDirection;

typedef struct {
  float pitch;
  float yaw;
  vec3 position;
  vec3 front;
  vec3 right;
  vec3 up;
  mat4 view;
} Camera;

Camera cameraInit(vec3 position, float pitch, float yaw);
void cameraProcessKeyboard(Camera *camera, CameraDirection direction);
void cameraProcessMouse(Camera *camera, float deltaX, float deltaY);
void cameraUpdateView(Camera *camera);

#endif // !CAMERA_H
