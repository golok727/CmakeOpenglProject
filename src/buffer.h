#pragma once
#include <glad/glad.h>

class Buffer
{
public:
  Buffer() : m_RendererId(0){};
  virtual ~Buffer()
  {
    glDeleteBuffers(1, &m_RendererId);
  }

  virtual void Bind() = 0;
  virtual void UnBind() = 0;

protected:
  GLuint m_RendererId;
};

class VertexBuffer : public Buffer
{
public:
  VertexBuffer(unsigned int size, void *data)
  {
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void Bind() override
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
  }

  void UnBind() override
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
};

class IndexBuffer : public Buffer
{
public:
  IndexBuffer(unsigned int size, void *data)
  {
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void Bind() override
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
  }

  void UnBind() override
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
};