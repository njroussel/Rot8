#define GLFW_INCLUDE_NONE

#include <rot8/triangle.h>
#include <rot8/window.h>

#include <iostream>

GLuint compileShader(GLenum shadertype, const GLchar* shaderSource) {
  GLuint shader = glCreateShader(shadertype);
  glShaderSource(shader, 1, &shaderSource, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER:::COMPILATION_FAILED\n"
              << "Information log:\n"
              << infoLog << std::endl;
    return 0;
  }

  return shader;
}

int main() {
  Window window(1280u, 720u);
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  // Create triangle
  GLfloat vertices[9] = {0.0,  0.5,  0.0,  //
                         -0.5, -0.5, 0.0,  //
                         0.5,  -0.5, 0.0};
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexBufferId;
  glGenBuffers(1, &vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void*)0);
  glEnableVertexAttribArray(0);

  // Shaders
  GLuint vShader = compileShader(GL_VERTEX_SHADER, triangleVShader);
  GLuint fShader = compileShader(GL_FRAGMENT_SHADER, triangleFShader);

  GLuint program = glCreateProgram();
  if (program == 0) {
    std::cerr << "Could not create program!" << std::endl;
    return EXIT_FAILURE;
  }
  glAttachShader(program, vShader);
  glAttachShader(program, fShader);
  glLinkProgram(program);
  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER:::LINKING_FAILED\n"
              << "Information log:\n"
              << infoLog << std::endl;
  }
  glUseProgram(program);
  glDeleteShader(vShader);
  glDeleteShader(fShader);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  window.renderWhileActive();

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}