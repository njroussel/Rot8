#include <rot8/helpers/shader.h>

#include <iostream>

GLuint compileShader(GLenum shadertype,
                     const std::filesystem::path& shaderPath) {
  return 0;
}

GLuint compileShader(GLenum shadertype, const GLchar* shaderSource) {
  GLuint shader = glCreateShader(shadertype);
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