#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <glad/glad.h>

typedef long Shader;

int shaderConstruct(Shader *shader, const char *vsPath, const char *fsPath);
void shaderUse(Shader shader);
void shaderSetFloat(Shader shader, const char *uniform, float value);

#endif
