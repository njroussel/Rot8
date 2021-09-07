#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <rot8/helpers/shader.h>
#include <rot8/helpers/vao.h>
#include <rot8/models/tex_triangle.h>

#include <cmath>
#include <filesystem>
#include <functional>
#include <iostream>

// fShader locations
const GLint COLOR_LOCATION{0};

// vShader locations
const GLint POSITION_LOCATION{0};
const GLint TEXCOORD_LOCATION{1};

TexTriangle::TexTriangle(GLuint vertexArray) : m_vao{vertexArray} {}

void TexTriangle::update() {
  float timeValue = static_cast<float>(glfwGetTime());

  const float downscale = 2.0F;
  const float offset = 0.5F;
  m_redValue = (std::cos(timeValue) / downscale) + offset;
}

void TexTriangle::render() const {
  auto renderSetup = [&]() {
    Shader::setVec4f(COLOR_LOCATION, m_redValue, 0, 0, 1.0F);
    getTexture().bindTexture();
    bindGeometry(m_vao);
  };

  getRenderable().render(renderSetup);
}

GLuint TexTriangle::initGeometry(
    std::array<float, TRIANGLE_VERTEX_COUNT * 3>& positions,
    std::array<float, TRIANGLE_VERTEX_COUNT * 2>& texCoords) {
  return createVAO(POSITION_LOCATION, positions, TEXCOORD_LOCATION, texCoords);
}

bool TexTriangle::isReady() { return getRenderable().isReady(); }

const Renderable& TexTriangle::getRenderable() {
  std::filesystem::path vShaderPath(
      "./src/models/tex_triangle/tex_triangle.vert");
  std::filesystem::path fShaderPath(
      "./src/models/tex_triangle/tex_triangle.frag");

  static Renderable renderable{vShaderPath, fShaderPath};

  return renderable;
}
const Texture& TexTriangle::getTexture() {
  std::filesystem::path texturePath("./res/textures/noise.jpg");

  static Texture texture{texturePath, TextureFormat::RGB, TextureFormat::RGB};

  return texture;
}