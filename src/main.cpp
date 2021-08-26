#include <rot8/drawable.h>
#include <rot8/helpers/shader.h>
#include <rot8/helpers/vao.h>
#include <rot8/window.h>

#include <iostream>

int main() {
  Window window(1280u, 720u);
  if (!window.wasCreated()) {
    return EXIT_FAILURE;
  }

  GLfloat vertices_1[9] = {-0.8f, 0.7f,  0.0f,  //
                           -0.8f, -0.8f, 0.0f,  //
                           0.7f,  -0.8f, 0.0f};
  GLfloat vertices_2[9] = {-0.7f, 0.8f,  0.0f,  //
                           0.8f,  -0.7f, 0.0f,  //
                           0.8f,  0.8f,  0.0f};

  GLuint vao_1 = createVAO(vertices_1, 9);
  GLuint vao_2 = createVAO(vertices_2, 9);

  Drawable triangle1{"./src/triangle/triangle.vert",
                     "./src/triangle/triangle.frag", vao_1};
  Drawable triangle2{"./src/triangle/triangle.vert",
                     "./src/triangle/triangle.frag", vao_2};
  if (!triangle1.isReady() || !triangle2.isReady()) {
    return EXIT_FAILURE;
  }

  std::vector<Drawable> drawables;
  drawables.push_back(std::move(triangle1));
  drawables.push_back(std::move(triangle2));

  window.renderWhileActive(drawables);

  std::cout << "Exiting..." << std::endl;
  return EXIT_SUCCESS;
}