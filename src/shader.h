#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
  Shader(const char *vertexSource, const char *fragmentSource);
  ~Shader();
  static Shader *LoadFromFile(const char *filepath);
  void setUniform1i(const char *name, int v);
  void setUniformMat4(const char *name, glm::mat4 &matrix);
  void use();
  void detach();

private:
  GLuint m_ProgramId;
  int getUniformLocation(const char *name);
};