#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <rot8/helpers/shader.h>
#include <rot8/helpers/vao.h>
#include <rot8/models/triangle.h>

#include <cmath>
#include <filesystem>
#include <functional>
#include <iostream>

const GLuint COLOR_LOCATION{0U};

Triangle::Triangle(GLuint triangleGeometry) : m_vao{triangleGeometry} {}

void Triangle::update() {
  float timeValue = static_cast<float>(glfwGetTime());

  const float downscale = 2.0F;
  const float offset = 0.5F;
  m_greenValue = (std::sin(timeValue) / downscale) + offset;
}

void Triangle::render() const {
  auto renderSetup = [&]() {
    Shader::setVec4f(COLOR_LOCATION, 0, m_greenValue, 0, 1.f);
    bindGeometry(m_vao);
  };

  getRenderable().render(renderSetup);
}

GLuint Triangle::initGeometry(const float* vertices) {
  return createVAO(3 * 3, vertices);
}

bool Triangle::isReady() { return getRenderable().isReady(); }

const Renderable& Triangle::getRenderable() {
  std::filesystem::path vShaderPath("./src/models/triangle/triangle.vert");
  std::filesystem::path fShaderPath("./src/models/triangle/triangle.frag");

  static Renderable renderable{vShaderPath, fShaderPath};

  return renderable;
}