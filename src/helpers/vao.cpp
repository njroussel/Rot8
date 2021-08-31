#include <rot8/helpers/vao.h>

GLuint createVAO(const GLfloat* vertices, GLsizei verticeCount) {
  GLuint vao{0U};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexBufferId{0U};
  glGenBuffers(1, &vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>((GLuint)verticeCount * sizeof(GLfloat)),
               vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void*)0);
  glEnableVertexAttribArray(0);

  return vao;
}