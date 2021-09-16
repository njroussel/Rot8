#include <rot8/helpers/shader.h>
#include <rot8/models/tex_triangle.h>
#include <rot8/models/triangle.h>
#include <rot8/renderable.h>
#include <rot8/window.h>

#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <iostream>
#include <span>

using namespace rot8;

constexpr uint16_t WINDOW_WIDTH = 1280U;
constexpr uint16_t WINDOW_HEIGHT = 720U;

int main() {
  Window window{WINDOW_WIDTH, WINDOW_HEIGHT};
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  glm::vec4 vec(1.0F, 0.0F, 0.0F, 1.0F);

  std::array<float, 3 * 3> vertices_1{-1.0F, 1.0F,  0.0F,  //
                                      -1.0F, -1.0F, 0.0F,  //
                                      1.0F,  -1.0F, 0.0F};

  std::array<float, 3 * 3> positions_2{-1.0F, 1.0F,  0.0F,  //
                                       1.0F,  1.0F,  0.0F,  //
                                       1.0F,  -1.0F, 0.0F};
  std::array<float, 3 * 2> texCoords_2{0.0F,       0.0F,  //
                                       1.0F / 2.F, 1.0F,  //
                                       1.0F,       0.0F};

  Triangle triangle{Triangle::initGeometry(&vertices_1[0])};
  TexTriangle textriangle{TexTriangle::initGeometry(positions_2, texCoords_2)};
  if (!Triangle::isReady() || !TexTriangle::isReady()) {
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