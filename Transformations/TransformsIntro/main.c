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
#define WIREFRAME_MODE 0

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

float alpha = 0.2f;
float lastTime = 0, currentTime, deltaTime;

// TODO: Transformations - Excercises

int main(void) {
  int x, y, nrChannels;
  unsigned VBO, VAO, EBO;
  unsigned textureObj;
  Shader shaderProgram;
  unsigned char *textureData;
  float vertices[] = {
    // Vertices         // Colors         // Texture Coordinates
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,           // Bottom-Left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,           // Top-Left
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,           // Bottom-Right
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f            // Top-Right
  };
  int indices[] = {
    0, 1, 2,
    1, 2, 3
  };
  GLFWwindow *window;

  // GLFW Initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window Creation
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLProject2", NULL, NULL);
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
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Program Creation
  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl")) {
    glfwTerminate();
    return -1;
  }
  shaderUse(shaderProgram);

  // Texture Data
  stbi_set_flip_vertically_on_load(true);

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Enables Wireframe Rendering
#if WIREFRAME_MODE
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

  unsigned transformLoc = glGetUniformLocation(shaderProgram, "transform");
  mat4 trans;
  glm_mat4_identity(trans);
  glm_translate(trans, (vec3){0.5f, -0.5f, 0.0f});

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Input
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    processInput(window);
    shaderSetFloat(shaderProgram, "alpha", alpha);
    /*** RENDER COMMANDS ***/
    // Background Color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
    // Draw
    glm_rotate(trans, glm_rad(ROTATION_SPEED * deltaTime), (vec3){0.0f, 0.0f, 1.0f});
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (float *)trans);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, NULL);

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
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
