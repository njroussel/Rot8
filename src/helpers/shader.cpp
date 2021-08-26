#include <rot8/helpers/shader.h>

#include <filesystem>
#include <fstream>
#include <iostream>

GLuint compileShader(GLenum shaderType,
                     const std::filesystem::path& shaderPath) {
  const GLuint SHADER_ERROR = 0;

  if (!std::filesystem::exists(shaderPath)) {
    std::cerr << "ERROR::SHADER:::PATH_DOES_NOT_EXIST\n"
              << "Following path for shader could not be found:\n"
              << shaderPath << std::endl;
    return SHADER_ERROR;
  }

  std::ifstream shaderStream{shaderPath};
  if (!shaderStream.is_open()) {
    std::cerr << "ERROR::SHADER:::PATH_COULD_NOT_OPEN\n"
              << "Following path for shader could not be opened:\n"
              << shaderPath << std::endl;
    return SHADER_ERROR;
  }
  std::string shaderSource{std::istreambuf_iterator<char>{shaderStream},
                           std::istreambuf_iterator<char>{}};

  return compileShader(shaderType, &shaderSource[0]);
}

GLuint compileShader(GLenum shaderType, const GLchar* shaderSource) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, nullptr);
  glCompileShader(shader);

  return checkCompilation(shader);
}

GLuint checkCompilation(GLuint shader) {
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint infoLogLength;
    ;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    std::string infoLog;
    infoLog.resize(static_cast<std::string::size_type>(infoLogLength));
    glGetShaderInfoLog(shader, infoLogLength, NULL, &infoLog[0]);

    std::cerr << "ERROR::SHADER:::COMPILATION_FAILED\n"
              << "Information log:\n"
              << infoLog << std::endl;
    return 0;
  }

  return shader;
}