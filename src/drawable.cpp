#include <glad/glad.h>
#include <rot8/drawable.h>
#include <rot8/helpers/shader.h>

#include <iostream>

Drawable::Drawable(std::filesystem::path vShaderPath,
                   std::filesystem::path fShaderPath, GLuint vao)
    : m_vao{vao} {
  GLuint vShader = compileShader(GL_VERTEX_SHADER, vShaderPath);
  GLuint fShader = compileShader(GL_FRAGMENT_SHADER, fShaderPath);
  if (vShader == 0 || fShader == 0) {
    return;
  }

  m_program = glCreateProgram();
  if (m_program == 0) {
    std::cerr << "ERROR::PROGRAM::CREATION_UNSUCCESSFUL\n"
              << "Could not create program !" << std::endl;
    return;
  }

  glAttachShader(m_program, vShader);
  glAttachShader(m_program, fShader);
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

  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

Drawable::~Drawable() {
  if (m_program != 0) {
    glDeleteProgram(m_program);
  }
}

Drawable::Drawable(Drawable&& rhs) noexcept
    : m_program{std::move(rhs.m_program)},
      m_vao{std::move(rhs.m_vao)} {
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
  glUseProgram(m_program);
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}