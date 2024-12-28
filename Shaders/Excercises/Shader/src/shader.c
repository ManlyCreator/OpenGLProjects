#include <shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO: Implement the shaderCompilationSuccess & programLinkSuccess functions

char *readFile(FILE *file);
int shaderCompilationSuccess(unsigned shader);
int programLinkSuccess(unsigned program);

int shaderConstruct(Shader *shader, const char *vsPath, const char *fsPath) {
  long fileSize;
  long vertexShader, fragmentShader;
  const char *vsSource;
  const char *fsSource;

  // Open Files
  FILE *vsFile = fopen(vsPath, "r");
  FILE *fsFile = fopen(fsPath, "r");

  if (!vsFile) {
    perror("Could not open Vertex Shader\n");
    return 0;
  }
  if (!fsFile) {
    perror("Could not open Fragment Shader\n");
    return 0;
  }

  // Vertex Shader
  vsSource = readFile(vsFile);
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vsSource, NULL);
  glCompileShader(vertexShader);
  if (!shaderCompilationSuccess(vertexShader)) {
    printf("Vertex Shader Compilation Failed\n");
    return 0;
  }

  // Fragment Shader
  fsSource = readFile(fsFile);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fsSource, NULL);
  glCompileShader(fragmentShader);
  if (!shaderCompilationSuccess(fragmentShader)) {
    printf("Fragment Shader Compilation Failed\n");
    return 0;
  }

  // Program Linking
  *shader = glCreateProgram();
  glAttachShader(*shader, vertexShader);
  glAttachShader(*shader, fragmentShader);
  glLinkProgram(*shader);
  if (!programLinkSuccess(*shader)) {
    printf("Program Linking Failed\n");
    return 0;
  }

  // Free Memory
  free((void *)vsSource);
  free((void *)fsSource);
  fclose(vsFile);
  fclose(fsFile);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return 1;
}

void shaderUse(Shader shader) {
  glUseProgram(shader);
}

void shaderSetFloat(Shader shader, const char *uniform, float value) {
  glUniform1f(glGetUniformLocation(shader, uniform), value);
}

char *readFile(FILE *file) {
  long size;
  char *src;

  fseek(file, 0, SEEK_END);
  size = ftell(file); 
  rewind(file);
  src = malloc(size + 1);
  fread(src, 1, size, file);
  src[size] = '\0';

  return src;
}

int shaderCompilationSuccess(unsigned shader) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("*** ERROR COMPILING SHADER ***\n%s", infoLog);
    return 0;
  }
  return 1;
}

int programLinkSuccess(unsigned program) {
  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("*** ERROR LINKING PROGRAM ***\n%s", infoLog);
    return 0;
  }
  return 1;
}
