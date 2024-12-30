// C Standard Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// OpenGL Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// TODO: Textures - Texture Units
// TODO: Set up a project that renders an untextured rectangle and contains the corresponding texture files.
//       Try to retexture the rectangle with nothing but OpenGL & stbi docs.

#define WIDTH 800
#define HEIGHT 600
#define BUF_SIZE 512
#define WIREFRAME_MODE 0

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

int main(void) {
  int width, height, nChannels;
  unsigned VBO, VAO, EBO;
  unsigned texture;
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

  // Texture Data
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

  textureData = stbi_load("../Textures/container.jpg", &width, &height, &nChannels, 0);
  if (textureData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  // Setting Vertex Array Data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

  if (!shaderConstruct(&shaderProgram, "../vertexShader.glsl", "../fragmentShader.glsl")) {
    glfwTerminate();
    return -1;
  }
  shaderUse(shaderProgram);

  // Callbacks
  glfwSetKeyCallback(window, keyCallback); 
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Enables Wireframe Rendering
#if WIREFRAME_MODE
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    /*** RENDER COMMANDS ***/
    // Transformations
    // float xOffset = sin(glfwGetTime() * 4) / 2;
    // float yOffset = cos(glfwGetTime() * 4) / 2;
    // shaderSetFloat(shaderProgram, "xOffset", xOffset);
    // shaderSetFloat(shaderProgram, "yOffset", yOffset);
    // Background Color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
    // Draw
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, NULL);

    /*** POLL EVENTS & SWAP BUFFERS ***/
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Free Memory
  stbi_image_free(textureData);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO); glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
