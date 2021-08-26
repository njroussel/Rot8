#pragma once

#include <glad/glad.h>

#include <filesystem>

GLuint compileShader(GLenum shadertype,
                     const std::filesystem::path& shaderPath);

GLuint compileShader(GLenum shadertype, const GLchar* shaderSource);

GLuint checkCompilation(GLuint shader);