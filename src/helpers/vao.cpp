#include <rot8/helpers/vao.h>

#include <cstring>
#include <iostream>
#include <vector>

GLuint createVAO(GLsizei verticeCount, const GLfloat* vertices) {
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

GLuint createVAO(GLint positionsLocation, const std::span<GLfloat>& positions,
                 GLint textureCoordsLocation,
                 const std::span<GLfloat>& textureCoords) {
  GLuint vao{0U};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexBufferId{0U};
  glGenBuffers(1, &vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

  unsigned long vertexPositionSize = 3 * sizeof(GLfloat);
  unsigned long vertexTexCoordSize = 2 * sizeof(GLfloat);

  const size_t vertexCount = positions.size() / 3;

  GLsizeiptr bufferSize =
      static_cast<GLsizeiptr>(vertexCount) *
      static_cast<GLsizeiptr>(vertexPositionSize + vertexTexCoordSize);
  std::vector<char> bufferData(static_cast<size_t>(bufferSize));

  size_t index{0};
  for (size_t i{0}; i < vertexCount; i++) {
    std::memcpy(&bufferData[index], &positions[i * 3], vertexPositionSize);
    index += vertexPositionSize;
    std::memcpy(&bufferData[index], &textureCoords[i * 2], vertexTexCoordSize);
    index += vertexTexCoordSize;
  }

  glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(
      positionsLocation, 3, GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(vertexPositionSize + vertexTexCoordSize), (void*)0);
  glEnableVertexAttribArray(positionsLocation);
  glVertexAttribPointer(
      textureCoordsLocation, 2, GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(vertexPositionSize + vertexTexCoordSize),
      (void*)vertexPositionSize);  // NOLINT
  glEnableVertexAttribArray(textureCoordsLocation);

  return vao;
}