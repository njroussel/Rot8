#pragma once

#include <glad/glad.h>

#include <filesystem>

class Texture {
 public:
  Texture(std::filesystem::path& texturePath);

  inline void bindTexture() const { glBindTexture(GL_TEXTURE_2D, m_texture); }

 private:
  GLuint m_texture{0U};
};