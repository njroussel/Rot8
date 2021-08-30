#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <rot8/helpers/shader.h>
#include <rot8/helpers/vao.h>
#include <rot8/models/triangle.h>

#include <cmath>
#include <filesystem>
#include <functional>
#include <iostream>

const GLuint COLOR_LOCATION{0u};

Triangle::Triangle(GLuint trianglGeometry) : m_vao{trianglGeometry} {}

void Triangle::update() {
  float timeValue = static_cast<float>(glfwGetTime());
  m_greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
}

void Triangle::render() const {
  auto renderSetup = [&]() {
    Shader::setVec4f(COLOR_LOCATION, 0, m_greenValue, 0, 1.f);
    bindGeometry(m_vao);
  };

  getRenderable().render(renderSetup);
}

GLuint Triangle::initGeometry(const float* vertices) {
  return createVAO(vertices, 9);
}

const Renderable& Triangle::getRenderable() const {
  std::filesystem::path vShaderPath("./src/models/triangle/triangle.vert");
  std::filesystem::path fShaderPath("./src/models/triangle/triangle.frag");

  static Renderable renderable{vShaderPath, fShaderPath};

  return renderable;
}