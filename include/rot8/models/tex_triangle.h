
#pragma once

#include <rot8/helpers/texture.h>>
#include <rot8/renderable.h>

#include <memory>
namespace rot8 {

const static size_t TRIANGLE_VERTEX_COUNT{3};
class TexTriangle {
 public:
  TexTriangle(GLuint vertexArray);

  void update();

  void render() const;

  static GLuint initGeometry(
      std::array<float, TRIANGLE_VERTEX_COUNT * 3>& postions,
      std::array<float, TRIANGLE_VERTEX_COUNT * 2>& texCoords);

  static bool isReady();

  static const Renderable& getRenderable();

  static const Texture& getTexture();

 private:
  float m_redValue{1.0F};
  GLuint m_vao;
};
}  // namespace rot8