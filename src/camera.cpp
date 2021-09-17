#include <rot8/camera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace rot8 {

Camera::Camera() : m_projectionType(ProjectionType::PERSPECTIVE) {}

void Camera::setProjectionType(ProjectionType projectionType) {}

}  // namespace rot8