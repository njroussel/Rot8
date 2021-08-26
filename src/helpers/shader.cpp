#include <rot8/helpers/shader.h>

#include <filesystem>
#include <fstream>
#include <iostream>

Shader::Shader(const GLenum shaderType,
               const std::filesystem::path& shaderPath) {
  if (!std::filesystem::exists(shaderPath)) {
    std::cerr << "ERROR::SHADER:::PATH_DOES_NOT_EXIST\n"
              << "Following path for shader could not be found:\n"
              << shaderPath << std::endl;
    return;
  }

  std::ifstream shaderStream{shaderPath};
  if (!shaderStream.is_open()) {
    std::cerr << "ERROR::SHADER:::PATH_COULD_NOT_OPEN\n"
              << "Following path for shader could not be opened:\n"
              << shaderPath << std::endl;
  }
  std::string shaderSource{std::istreambuf_iterator<char>{shaderStream},
                           std::istreambuf_iterator<char>{}};

  fromSource(shaderType, &shaderSource[0]);
  checkCompilation();
}

Shader::Shader(const GLenum shaderType, const GLchar* shaderSource) {
  fromSource(shaderType, shaderSource);
  checkCompilation();
}

Shader::~Shader() { glDeleteShader(m_shader); }

Shader::Shader(Shader&& rhs) noexcept : m_shader{rhs.m_shader} {
  rhs.m_shader = 0;
}

Shader& Shader::operator=(Shader&& rhs) noexcept {
  if (this != &rhs) {
    m_shader = rhs.m_shader;

    rhs.m_shader = 0;
  }

  return *this;
}

void Shader::fromSource(const GLenum shaderType, const GLchar* shaderSource) {
  m_shader = glCreateShader(shaderType);
  glShaderSource(m_shader, 1, &shaderSource, nullptr);
  glCompileShader(m_shader);
}

void Shader::checkCompilation() {
  GLint success;
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint infoLogLength;
    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    std::string infoLog;
    infoLog.resize(static_cast<size_t>(infoLogLength));
    glGetShaderInfoLog(m_shader, infoLogLength, NULL, &infoLog[0]);

    std::cerr << "ERROR::SHADER:::COMPILATION_FAILED\n"
              << "Information log:\n"
              << infoLog << std::endl;
    m_shader = 0;
  }
}