#pragma once

#include <rot8/renderable.h>

#include <memory>

namespace rot8 {
class Triangle {
 public:
  Triangle(GLuint triangleGeometry);

  void update();

  void render() const;

  static GLuint initGeometry(const float* vertices);

  static bool isReady();

  static const Renderable& getRenderable();

 private:
  float m_greenValue{1.0F};
  GLuint m_vao;
};
}  // namespace rot8