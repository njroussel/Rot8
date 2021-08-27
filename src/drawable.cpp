#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <rot8/drawable.h>
#include <rot8/helpers/shader.h>

#include <cmath>
#include <iostream>

Drawable::Drawable(std::filesystem::path vShaderPath,
                   std::filesystem::path fShaderPath, GLuint vao)
    : m_vao{vao} {
  Shader vShader{GL_VERTEX_SHADER, vShaderPath};
  Shader fShader{GL_FRAGMENT_SHADER, fShaderPath};
  if (!vShader.isValid() || !fShader.isValid()) {
    return;
  }

  m_program = glCreateProgram();
  if (m_program == 0) {
    std::cerr << "ERROR::PROGRAM::CREATION_UNSUCCESSFUL\n"
              << "Could not create program !" << std::endl;
    return;
  }

  glAttachShader(m_program, vShader.getId());
  glAttachShader(m_program, fShader.getId());
  glLinkProgram(m_program);

  GLint success;
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (!success) {
    GLint infoLogLength;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

    std::string infoLog;
    infoLog.resize(static_cast<size_t>(infoLogLength));
    glGetProgramInfoLog(m_program, infoLogLength, NULL, &infoLog[0]);

    std::cerr << "ERROR::SHADER:::LINKING_FAILED\n"
              << "Information log:\n"
              << infoLog << std::endl;
    return;
  }
}

Drawable::~Drawable() {
  if (m_program != 0) {
    glDeleteProgram(m_program);
  }
}

Drawable::Drawable(Drawable&& rhs) noexcept
    : m_program{std::move(rhs.m_program)}, m_vao{std::move(rhs.m_vao)} {
  rhs.m_program = 0;
  rhs.m_vao = 0;
}

Drawable& Drawable::operator=(Drawable&& rhs) noexcept {
  m_program = std::move(rhs.m_program);
  m_vao = std::move(rhs.m_vao);

  rhs.m_program = 0;
  rhs.m_vao = 0;

  return *this;
}

bool Drawable::isReady() {
  GLint linkSuccess;
  glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);

  return m_program != 0 && linkSuccess != 0;
}

void Drawable::draw() const {
  float timeValue = static_cast<float>(glfwGetTime());
  float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;

  glUseProgram(m_program);
  glUniform4f(0, 0.0f, greenValue, 0.0f, 1.0f);

  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}