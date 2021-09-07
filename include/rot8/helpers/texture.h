#pragma once

#include <glad/glad.h>

#include <filesystem>

enum TextureFormat {
  RGB = GL_RGB,
  RGBA = GL_RGBA,
};

class Texture {
 public:
  Texture(std::filesystem::path& texturePath, TextureFormat inputTexture,
          TextureFormat desiredFormat);

  inline void bindTexture() const { glBindTexture(GL_TEXTURE_2D, m_texture); }

 private:
  GLuint m_texture{0U};
};