#include <rot8/window.h>

#include <algorithm>
#include <iostream>

Window::Window(const uint16_t width, const uint16_t height)
    : m_width(width), m_height(height), m_successInit(true), m_window(nullptr) {
  if (!glfwInit()) {
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
  if (!m_window) {
    std::cerr << "GLFW could not create a window!" << std::endl;
    m_successInit = false;
    return;
  }
  glfwMakeContextCurrent(m_window);

  // Setup GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return;
  }

  glViewport(0, 0, m_width, m_height);
  glfwSetWindowCloseCallback(m_window, destroyWindowOnClose);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);  // V-sync
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

Window::~Window() { glfwTerminate(); }

bool Window::wasCreated() const { return m_successInit; }

void Window::render(std::vector<Drawable> &drawables) const {
  processInput(m_window);

  glClear(GL_COLOR_BUFFER_BIT);
  std::for_each(drawables.begin(), drawables.end(),
                [&](const Drawable &drawable) { drawable.draw(); });

  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

bool Window::isActive() const { return !glfwWindowShouldClose(m_window); }

void Window::renderWhileActive(std::vector<Drawable> &drawables) const {
  while (isActive()) {
    render(drawables);
  }
}

void Window::destroyWindowOnClose(GLFWwindow *window) {
  glfwDestroyWindow(window);
}

void Window::processInput(GLFWwindow *const window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
