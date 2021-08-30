#pragma once

#include <glad/glad.h>

#include <filesystem>

class Shader {
 public:
  Shader(GLenum shaderType, const std::filesystem::path& shaderPath);

  Shader(GLenum shaderType, const GLchar* shaderSource);

  ~Shader();

  Shader(Shader const& rhs) = delete;

  Shader& operator=(Shader const& rhs) = delete;

  Shader(Shader&& rhs) noexcept;

  Shader& operator=(Shader&& rhs) noexcept;

  inline bool isValid() const { return m_shader != 0; }

  inline GLuint getId() const { return m_shader; }

  static void setVec4f();

 private:
  void fromSource(const GLenum shaderType, const GLchar* shaderSource);

  void checkCompilation();

  GLuint m_shader{0};
};