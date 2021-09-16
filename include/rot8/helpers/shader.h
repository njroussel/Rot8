#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rot8 {

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

  inline static void setMat4f(const GLint location, const glm::mat4& mat) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
  }

  inline static void setMat4f(const GLint location, const GLfloat* ptr) {
    glUniformMatrix4fv(location, 1, GL_FALSE, ptr);
  }

  inline static void setVec4f(const GLint location, const GLfloat x,
                              const GLfloat y, const GLfloat z,
                              const GLfloat w) {
    glUniform4f(location, x, y, z, w);
  }

  inline static void setVec2f(const GLint location, const GLfloat x,
                              const GLfloat y) {
    glUniform2f(location, x, y);
  }

 private:
  void fromSource(const GLenum& shaderType, const GLchar* shaderSource);

  void checkCompilation();

  GLuint m_shader{0};
};

}  // namespace rot8