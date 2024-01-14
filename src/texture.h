#pragma once
#include <glad/glad.h>
class Texture
{
public:
  Texture(const char *filepath);
  ~Texture();
  void use(unsigned int slot = 0) const;
  void detach() const;

private:
  GLuint m_TextureId;
  int m_Width;
  int m_Height;
  int m_NChannels;
};
