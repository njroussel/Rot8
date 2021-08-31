#pragma once

#include <glad/glad.h>

#include <filesystem>

class Texture {
 public:
  Texture(std::filesystem::path& texturePath);

 private:
  GLuint m_texture{0U};
  int m_width{0};
  int m_height{0};
  int m_channels{0};
};