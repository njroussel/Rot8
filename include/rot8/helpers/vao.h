#pragma once

#include <glad/glad.h>

#include <span>

GLuint createVAO(GLsizei verticeCount, const GLfloat* vertices);

GLuint createVAO(GLint positionsLocation, const std::span<GLfloat>& positions,
                 GLint textureCoordsLocation,
                 const std::span<GLfloat>& textureCoords);

inline void bindGeometry(GLuint vao) { glBindVertexArray(vao); }