#pragma once

#include <glad/glad.h>

GLuint createVAO(const GLfloat* vertices, GLsizei verticeCount);

inline void bindGeometry(GLuint vao) { glBindVertexArray(vao); }