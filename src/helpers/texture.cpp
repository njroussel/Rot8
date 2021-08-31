#define STB_IMAGE_IMPLEMENTATION
#include <rot8/helpers/texture.h>
#include <stb_image.h>

#include <iostream>

Texture::Texture(std::filesystem::path& texturePath) {
  if (!std::filesystem::exists(texturePath)) {
    std::cerr << "ERROR::TEXTURE::PATH_DOES_NOT_EXIST\n"
              << "Following path for texture could not be found:\n"
              << texturePath << std::endl;
    return;
  }

  unsigned char* data =
      stbi_load(texturePath.c_str(), &m_width, &m_height, &m_channels, 0);
  if (data == nullptr) {
    std::cerr << "ERROR::TEXTURE::IMAGE_CANNOT_BE_LOADED\n"
              << "Image data could not be loaded for file:\n"
              << texturePath << std::endl;
    return;
  }

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}