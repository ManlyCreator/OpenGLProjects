#ifndef SHADER_H
#define SHADER_H

typedef unsigned Shader;

int shaderConstruct(Shader *shader, const char *vsPath, const char *fsPath);
void shaderUse(Shader shader);
void shaderSetInt(Shader shader, const char *uniform, int value);
void shaderSetFloat(Shader shader, const char *uniform, float value);

#endif // !SHADER_H
