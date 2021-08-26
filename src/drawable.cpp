#include <glad/glad.h>
#include <rot8/drawable.h>
#include <rot8/helpers/shader.h>

#include <iostream>

Drawable::Drawable(std::filesystem::path vShaderPath,
                   std::filesystem::path fShaderPath, GLuint vao)
    : m_vao{vao} {
  m_vShader = compileShader(GL_VERTEX_SHADER, vShaderPath);
  m_fShader = compileShader(GL_FRAGMENT_SHADER, fShaderPath);
  if (m_vShader == 0 || m_fShader == 0) {
    return;
  }

  m_program = glCreateProgram();
  if (m_program == 0) {
    std::cerr << "ERROR::PROGRAM::CREATION_UNSUCCESSFUL\n"
              << "Could not create program !" << std::endl;
    return;
  }

  glAttachShader(m_program, m_vShader);
  glAttachShader(m_program, m_fShader);
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

  glDeleteShader(m_vShader);
  glDeleteShader(m_fShader);
}

Drawable::~Drawable() {
  if (m_program != 0) {
    glDeleteProgram(m_program);
  }
}

Drawable::Drawable(Drawable&& rhs) noexcept
    : m_vShader{std::move(rhs.m_vShader)},
      m_fShader{std::move(rhs.m_fShader)},
      m_program{std::move(rhs.m_program)},
      m_vao{std::move(rhs.m_vao)} {
  rhs.m_vShader = 0;
  rhs.m_fShader = 0;
  rhs.m_program = 0;
  rhs.m_vao = 0;
}

Drawable& Drawable::operator=(Drawable&& rhs) noexcept {
  m_vShader = std::move(rhs.m_vShader);
  m_fShader = std::move(rhs.m_fShader);
  m_program = std::move(rhs.m_program);
  m_vao = std::move(rhs.m_vao);

  rhs.m_vShader = 0;
  rhs.m_fShader = 0;
  rhs.m_program = 0;
  rhs.m_vao = 0;

  return *this;
}

bool Drawable::isReady() {
  GLint linkSuccess;
  glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);

  return m_vShader != 0 && m_fShader != 0 && m_program != 0 && linkSuccess != 0;
}

void Drawable::draw() const {
  glUseProgram(m_program);
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  /*
  GLint infoLogLength;
  glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
  std::string infoLog;
  infoLog.resize(infoLogLength);
  glGetProgramInfoLog(m_program, infoLogLength, NULL, &infoLog[0]);
  std::cout << "Program information log:\n"
            << infoLog << std::endl;

  glGetShaderiv(m_fShader, GL_INFO_LOG_LENGTH, &infoLogLength);
  infoLog.resize(static_cast<std::string::size_type>(infoLogLength));
  glGetShaderInfoLog(m_fShader, infoLogLength, NULL, &infoLog[0]);
  std::cerr << "Shader information log:\n"
            << infoLog << std::endl;
  */
}