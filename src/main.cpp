#include <rot8/helpers/shader.h>
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

  Triangle triangle1{Triangle::initGeometry(vertices_1)};
  Triangle triangle2{Triangle::initGeometry(vertices_2)};
  if (!triangle1.isReady() || !triangle2.isReady()) {
    return EXIT_FAILURE;
  }

  std::vector<Triangle> triangles;
  triangles.push_back(std::move(triangle1));
  triangles.push_back(std::move(triangle2));

  while (window.isActive()) {
    window.prerender();
    std::for_each(triangles.begin(), triangles.end(), [&](Triangle& triangle) {
      triangle.update();
      triangle.render();
    });
    window.postrender();
  }

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}