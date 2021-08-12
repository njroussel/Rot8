#define GLFW_INCLUDE_NONE

#include <rot8/window.h>

#include <iostream>

int main() {
  Window window(1280u, 720u);
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  window.renderWhileActive();

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}