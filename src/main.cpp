#define GLFW_INCLUDE_NONE

#include <rot8/window.h>

#include <iostream>

int main() {
  Window window(1280u, 720u);
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  window.renderWhileActive();

  float vertices[9] = {0.0,  0.5,  0.0,  //
                       -0.5, -0.5, 0.0,  //
                       0.5,  -0.5, 0.0};

  uint32_t vertexBufferId;
  glGenBuffers(1, &vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}