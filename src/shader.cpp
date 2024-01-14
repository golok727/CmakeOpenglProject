#include "shader.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertexSource, const char *fragmentSource)
{

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexSource, 0);
  glCompileShader(vertexShader);

  GLint isCompiled = 0;

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(vertexShader);

    std::cerr << "Error Compiling VertexShader:\n"
              << infoLog.data() << std::endl;
    return;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentSource, 0);

  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    std::cerr << "Error Compiling FragmentShader:\n " << infoLog.data() << std::endl;
    return;
  }

  m_ProgramId = glCreateProgram();

  GLuint program = m_ProgramId;

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cerr << "Error Linking Program:\n"
              << infoLog.data() << std::endl;
    return;
  }

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
}

Shader::~Shader()
{
  glDeleteProgram(m_ProgramId);
}

Shader *Shader::LoadFromFile(const char *filepath)
{
  std::ifstream shaderFile(filepath);
  if (!shaderFile.is_open())
  {
    std::cerr << "Error loading shader file does not exits" << std::endl;
    return nullptr;
  }
  const int T_NONE = -1, T_VERTEX = 0, T_FRAGMENT = 1;

  int currentShaderType = T_NONE;

  std::string line;
  std::stringstream ss[2];
  while (std::getline(shaderFile, line))
  {
    if (line.find("@type") != std::string::npos)
    {
      if (line.find("@type vertex") != std::string::npos)
        currentShaderType = T_VERTEX;

      else if (line.find("@type fragment") != std::string::npos)
        currentShaderType = T_FRAGMENT;

      continue;
    }

    if (currentShaderType == T_NONE)
      continue;

    ss[currentShaderType] << line << "\n";
  }

  std::string vertexSrc = ss[T_VERTEX].str();
  std::string fragmentSrc = ss[T_FRAGMENT].str();

  return new Shader(vertexSrc.c_str(), fragmentSrc.c_str());
}

void Shader::setUniform1i(const char *name, int v)
{
  int location = getUniformLocation(name);
  glUniform1i(location, v);
}

void Shader::setUniformMat4(const char *name, glm::mat4 &matrix)
{
  int location = getUniformLocation(name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::use()
{
  glUseProgram(m_ProgramId);
}

void Shader::detach()
{
  glUseProgram(0);
}

int Shader::getUniformLocation(const char *name)
{
  int location = glGetUniformLocation(m_ProgramId, name);
  if (location < 0)
    std::cout << "Uniform with name " << name << " is not set; \n";
  return location;
}
