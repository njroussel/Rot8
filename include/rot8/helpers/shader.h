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

  inline static void setVec4f(GLint location, GLfloat x, GLfloat y, GLfloat z,
                              GLfloat w) {
    glUniform4f(location, x, y, z, w);
  }

  inline static void setVec2f(GLint location, GLfloat x, GLfloat y) {
    glUniform2f(location, x, y);
  }

 private:
  void fromSource(const GLenum& shaderType, const GLchar* shaderSource);

  void checkCompilation();

  GLuint m_shader{0};
};