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

  int width{0};
  int height{0};
  int channels{0};
  unsigned char* data =
      stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
  if (data == nullptr) {
    std::cerr << "ERROR::TEXTURE::IMAGE_CANNOT_BE_LOADED\n"
              << "Image data could not be loaded for file:\n"
              << texturePath << std::endl;
    return;
  }

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  stbi_image_free(data);
}