
#pragma once

#include <rot8/renderable.h>

#include <memory>

class TexTriangle {
 public:
  TexTriangle(GLuint triangleGeometry);

  inline bool isReady() const { return getRenderable().isReady(); }

  void update();

  void render() const;

  static GLuint initGeometry(const float* vertices);

  const Renderable& getRenderable() const;

 private:
  float m_greenValue{1.f};
  GLuint m_vao;
};