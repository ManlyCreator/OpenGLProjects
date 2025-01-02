// C Standard Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// OpenGL Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include <cglm/cglm.h>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 800
#define HEIGHT 600
#define BUF_SIZE 512
#define ALPHA_SPEED 1.0f
#define ROTATION_SPEED 45.0f
#define CAMERA_MOVE_SPEED 3.0f
#define WIREFRAME_MODE 0

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

float alpha = 0.2f;
float lastTime = 0, currentTime, deltaTime;
float xMove = 0.0f, yMove = 0.0f, zMove = 0.0f;

int main(void) {
  int x, y, nrChannels;
  unsigned VBO, VAO;
  unsigned textureObj;
  Shader shaderProgram;
  unsigned char *textureData;
  float vertices[] = {
      // Vertices          // Texture Coordinates
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  GLFWwindow *window;
  vec3 cubePositions[] = {
    {0.0f,  0.0f,  -3.0f}, 
    {2.0f,  5.0f, -15.0f}, 
    {-1.5f, -2.2f, -2.5f},  
    {-3.8f, -2.0f, -12.3f},  
    { 2.4f, -0.4f, -3.5f},  
    {-1.7f,  3.0f, -7.5f},  
    { 1.3f, -2.0f, -2.5f},  
    { 1.5f,  2.0f, -2.5f}, 
    { 1.5f,  0.2f, -1.5f}, 
    {-1.3f,  1.0f, -1.5f}  
};

  // GLFW Initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window Creation
  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME_MACRO, NULL, NULL);
  if (!window) {
    printf("*** WINDOW CREATION FAILED ***\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  // GLAD Initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("*** GLAD INITIALIZATION FAILED ***\n");
    return -1;
  }
  glViewport(0, 0, WIDTH, HEIGHT);

  // Vertex Array Buffer
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Element Buffer Object
  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Program Creation
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl")) {
    glfwTerminate();
    return -1;
  }
  shaderUse(shaderProgram);

  // Texture Data
  glGenTextures(1, &textureObj);
  glBindTexture(GL_TEXTURE_2D, textureObj);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glActiveTexture(GL_TEXTURE0);
  textureData = stbi_load("../Textures/container.jpg", &x, &y, &nrChannels, 0);
  if (textureData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  glActiveTexture(GL_TEXTURE1);
  textureData = stbi_load("../Textures/awesomeface.png", &x, &y, &nrChannels, 0);
  if (textureData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  shaderSetInt(shaderProgram, "texture1", 0);
  shaderSetInt(shaderProgram, "texture2", 1);

  // Setting Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Enables Wireframe Rendering
#if WIREFRAME_MODE
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

  // Transformations
  unsigned perspectiveLoc = glGetUniformLocation(shaderProgram, "perspective");
  unsigned viewLoc = glGetUniformLocation(shaderProgram, "view");
  unsigned modelLoc = glGetUniformLocation(shaderProgram, "model");
  mat4 perspective, view, model;
  
  // Render Loop
  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window)) {
    // Input
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    processInput(window);
    /*** RENDER COMMANDS ***/
    // Background Color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    // Draw
    for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
      float angle = i * 20.0f;
      // Perspective Matrix
      glm_mat4_identity(perspective);
      glm_perspective(glm_rad(45.0f), (float)WIDTH / HEIGHT, 0.1, 100.0f, perspective);
      // View (Camera) Matrix
      glm_mat4_identity(view);
      glm_translate(view, (vec3){cubePositions[i][0] + xMove, cubePositions[i][1] + yMove, cubePositions[i][2] + zMove});
      // Model Matrix
      glm_mat4_identity(model);
      if (i % 3 == 0)
        angle += glfwGetTime() * 100.0f;
      glm_rotate(model, glm_rad(angle), (vec3){0.5f, 0.5f, 0.0f});
      // Setting Uniforms
      glUniformMatrix4fv(perspectiveLoc, 1,  GL_FALSE, (float *)perspective);
      glUniformMatrix4fv(viewLoc, 1,  GL_FALSE, (float *)view);
      glUniformMatrix4fv(modelLoc, 1,  GL_FALSE, (float *)model);
      // Drawing Cubes
      glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
    }

    /*** POLL EVENTS & SWAP BUFFERS ***/
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Free Memory
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO); glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    alpha = (alpha + (ALPHA_SPEED * deltaTime) > 1 ? 1 : alpha + (ALPHA_SPEED * deltaTime));

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    alpha = (alpha - (ALPHA_SPEED * deltaTime) < 0 ? 0 : alpha - (ALPHA_SPEED * deltaTime));

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    xMove += CAMERA_MOVE_SPEED * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    xMove -= CAMERA_MOVE_SPEED * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    zMove += CAMERA_MOVE_SPEED * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    zMove -= CAMERA_MOVE_SPEED * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    yMove += CAMERA_MOVE_SPEED * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    yMove -= CAMERA_MOVE_SPEED * deltaTime;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
