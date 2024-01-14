#include "texture.h"
#include "stb_image.h"
#include <iostream>
Texture::Texture(const char *filepath) : m_TextureId(0), m_Width(0), m_Height(0), m_NChannels(0)
{
  glGenTextures(1, &m_TextureId);
  glBindTexture(GL_TEXTURE_2D, m_TextureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  stbi_set_flip_vertically_on_load(true);

  stbi_uc *data = stbi_load(filepath, &m_Width, &m_Height, &m_NChannels, 0);

  int imgDataFormat = 0;
  if (m_NChannels == 3)
    imgDataFormat = GL_RGB;

  else if (m_NChannels == 4)
    imgDataFormat = GL_RGBA;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, imgDataFormat, GL_UNSIGNED_BYTE, data);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_TextureId);
}

void Texture::use(unsigned int slot) const
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::detach() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
