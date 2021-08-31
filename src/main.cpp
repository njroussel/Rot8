#include <rot8/helpers/shader.h>
#include <rot8/models/tex_triangle.h>
#include <rot8/models/triangle.h>
#include <rot8/renderable.h>
#include <rot8/window.h>

#include <algorithm>
#include <iostream>

int main() {
  Window window(1280u, 720u);
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  float vertices_1[9] = {-0.8f, 0.7f,  0.0f,  //
                         -0.8f, -0.8f, 0.0f,  //
                         0.7f,  -0.8f, 0.0f};
  float vertices_2[9] = {-0.7f, 0.8f,  0.0f,  //
                         0.8f,  -0.7f, 0.0f,  //
                         0.8f,  0.8f,  0.0f};

  Triangle triangle{Triangle::initGeometry(vertices_1)};
  TexTriangle textriangle{TexTriangle::initGeometry(vertices_2)};
  if (!triangle.isReady() || !textriangle.isReady()) {
    return EXIT_FAILURE;
  }

  while (window.isActive()) {
    window.prerender();
    triangle.update();
    textriangle.update();

    triangle.render();
    textriangle.render();
    window.postrender();
  }

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}