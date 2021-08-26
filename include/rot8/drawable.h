#pragma once

#include <glad/glad.h>

#include <filesystem>

class Drawable {
 public:
  Drawable(std::filesystem::path vShaderPath, std::filesystem::path fShaderPath,
           GLuint vao);

  ~Drawable();

  Drawable(Drawable const& rhs) = delete;

  Drawable& operator=(Drawable const& rhs) = delete;

  Drawable(Drawable&& rhs) noexcept;

  Drawable& operator=(Drawable&& rhs) noexcept;

  bool isReady();

  void draw() const;

 private:
  GLuint m_program{0};
  GLuint m_vao;
};
