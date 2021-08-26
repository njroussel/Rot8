#pragma once

#include <glad/glad.h>

#include <filesystem>

GLuint compileShader(GLenum shaderType,
                     const std::filesystem::path& shaderPath);

GLuint compileShader(GLenum shaderType, const GLchar* shaderSource);

GLuint checkCompilation(GLuint shader);