#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <functional>

namespace rot8 {
class Renderable {
 public:
  Renderable(std::filesystem::path& vShaderPath,
             std::filesystem::path& fShaderPath);

  ~Renderable();

  Renderable(Renderable const& rhs) = delete;

  Renderable& operator=(Renderable const& rhs) = delete;

  Renderable(Renderable&& rhs) noexcept;

  Renderable& operator=(Renderable&& rhs) noexcept;

  bool isReady() const;

  void render(const std::function<void()>& renderSetup) const;

 private:
  GLuint m_program{0};
};

}  // namespace rot8