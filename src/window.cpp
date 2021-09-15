#include <rot8/window.h>

#include <algorithm>
#include <iostream>

namespace rot8 {
constexpr float CLEAR_COLOR_R = 0.2F;
constexpr float CLEAR_COLOR_G = 0.3F;
constexpr float CLEAR_COLOR_B = 0.3F;

Window::Window(const uint16_t width, const uint16_t height)
    : m_width(width), m_height(height), m_successInit(true), m_window(nullptr) {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "GLFW could not init!" << std::endl;
    m_successInit = false;
    return;
  }

  // Setup GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

  // Create GLFW window
  m_window = glfwCreateWindow(m_width, m_height, "Rot8", NULL, NULL);
  if (m_window == nullptr) {
    std::cerr << "GLFW could not create a window!" << std::endl;
    m_successInit = false;
    return;
  }
  glfwMakeContextCurrent(m_window);

  // Setup GLAD
  if (gladLoadGLLoader(
          reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==  // NOLINT
      0) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return;
  }

  glViewport(0, 0, m_width, m_height);
  glfwSetWindowCloseCallback(m_window, destroyWindowOnClose);
  glfwSwapInterval(1);  // V-sync
  glClearColor(CLEAR_COLOR_R, CLEAR_COLOR_G, CLEAR_COLOR_B, 1.0F);
}

Window::~Window() { glfwTerminate(); }

bool Window::wasCreated() const { return m_successInit; }

void Window::prerender() const {
  processInput(m_window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::postrender() const {
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

bool Window::isActive() const {
  return glfwWindowShouldClose(m_window) == GLFW_FALSE;
}

void Window::destroyWindowOnClose(GLFWwindow *window) {
  glfwDestroyWindow(window);
}

void Window::processInput(GLFWwindow *const window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

}  // namespace rot8