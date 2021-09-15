#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <rot8/renderable.h>

#include <vector>
namespace rot8 {
class Window {
 public:
  Window(const uint16_t width, const uint16_t height);

  ~Window();

  bool wasCreated() const;

  void prerender() const;

  void postrender() const;

  bool isActive() const;

 private:
  static void destroyWindowOnClose(GLFWwindow *const window);

  static void processInput(GLFWwindow *const window);

  const uint16_t m_width;
  const uint16_t m_height;
  bool m_successInit;
  GLFWwindow *m_window;
};
}  // namespace rot8