#pragma once

#include <rot8/renderable.h>

#include <memory>

class Triangle {
 public:
  Triangle(GLuint triangleGeometry);

  ~Triangle();

  Triangle(Triangle const& rhs);

  Triangle& operator=(Triangle const& rhs);

  Triangle(Triangle&& rhs) noexcept;

  Triangle& operator=(Triangle&& rhs) noexcept;

  inline bool isReady() const { return m_renderable->isReady(); }

  void update();

  void render() const;

  const Renderable& getRenderable() const { return *m_renderable; };

  static GLuint initGeometry(const float* vertices);

 private:
  static std::unique_ptr<Renderable> initRenderable();

  float m_greenValue{1.f};
  GLuint m_vao;

  static std::unique_ptr<Renderable> m_renderable;
};