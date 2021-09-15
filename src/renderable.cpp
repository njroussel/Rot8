#include <rot8/helpers/shader.h>
#include <rot8/renderable.h>

#include <iostream>

namespace rot8 {

Renderable::Renderable(std::filesystem::path& vShaderPath,
                       std::filesystem::path& fShaderPath) {
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

  GLint success{GL_TRUE};
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint infoLogLength{0};
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

Renderable::~Renderable() {
  if (m_program != 0) {
    glDeleteProgram(m_program);
  }
}

Renderable::Renderable(Renderable&& rhs) noexcept : m_program{rhs.m_program} {
  rhs.m_program = 0;
}

Renderable& Renderable::operator=(Renderable&& rhs) noexcept {
  m_program = rhs.m_program;
  rhs.m_program = 0;

  return *this;
}

bool Renderable::isReady() const {
  GLint linkSuccess{GL_TRUE};
  glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);

  return m_program != 0 && linkSuccess != 0;
}

void Renderable::render(const std::function<void()>& renderSetup) const {
  glUseProgram(m_program);
  renderSetup();
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
}  // namespace rot8