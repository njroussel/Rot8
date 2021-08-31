
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <rot8/helpers/shader.h>
#include <rot8/helpers/vao.h>
#include <rot8/models/tex_triangle.h>

#include <cmath>
#include <filesystem>
#include <functional>
#include <iostream>

const GLuint COLOR_LOCATION{0U};

TexTriangle::TexTriangle(GLuint triangleGeometry) : m_vao{triangleGeometry} {}

void TexTriangle::update() { m_greenValue = 1.0F; }

void TexTriangle::render() const {
  auto renderSetup = [&]() {
    Shader::setVec4f(COLOR_LOCATION, 0, m_greenValue, 0, 1.0F);
    bindGeometry(m_vao);
  };

  getRenderable().render(renderSetup);
}

GLuint TexTriangle::initGeometry(const float* vertices) {
  return createVAO(vertices, 3 * 3);
}

bool TexTriangle::isReady() { return getRenderable().isReady(); }

const Renderable& TexTriangle::getRenderable() {
  std::filesystem::path vShaderPath("./src/models/triangle/triangle.vert");
  std::filesystem::path fShaderPath("./src/models/triangle/triangle.frag");

  static Renderable renderable{vShaderPath, fShaderPath};

  return renderable;
}