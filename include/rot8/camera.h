#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <variant>

namespace rot8 {

enum ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

const float ORTHO_LEFT_DEFAULT{0.0F};
const float ORTHO_RIGHT_DEFAULT{1280.0F};
const float ORTHO_BOTTOM_DEFAULT{0.0F};
const float ORTHO_TOP_DEFAULT{720.0F};
const float ORTHO_NEAR_DEFAULT{0.01F};
const float ORTHO_FAR_DEFAULT{1000.0F};

struct OrthographicProjection {
  float left{ORTHO_LEFT_DEFAULT};
  float right{ORTHO_RIGHT_DEFAULT};
  float bottom{ORTHO_BOTTOM_DEFAULT};
  float top{ORTHO_TOP_DEFAULT};
  float near{ORTHO_NEAR_DEFAULT};
  float far{ORTHO_FAR_DEFAULT};

  inline glm::mat4 toMatrix() const {
    return glm::ortho(left, right, bottom, top, near, far);
  }
};

const float PERSP_FOV_DEG_DEFAULT{45.0F};
const float PERSP_ASPECT_RATIO_DEFAULT{1280.0F / 720.0F};
const float PERSP_NEAR_DEFAULT{0.01F};
const float PERSP_FAR_DEFAULT{1000.0F};

struct PerspectiveProjection {
  float fovRad{glm::radians(PERSP_FOV_DEG_DEFAULT)};
  float aspectRatio{PERSP_ASPECT_RATIO_DEFAULT};
  float near{PERSP_NEAR_DEFAULT};
  float far{PERSP_FAR_DEFAULT};

  inline glm::mat4 toMatrix() const {
    return glm::perspective(fovRad, aspectRatio, near, far);
  }
};

class Camera {
 public:
  Camera();

  void setProjectionType(ProjectionType projectionType);

  inline ProjectionType getProjectionType() const { return m_projectionType; }

 private:
  glm::mat4 m_projectionMat{PerspectiveProjection().toMatrix()};
  std::variant<OrthographicProjection, PerspectiveProjection> m_projection{
      PerspectiveProjection};
  ProjectionType m_projectionType{PERSPECTIVE};
};

}  // namespace rot8