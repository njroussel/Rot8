#version 460 core

layout(location = 0) in vec3 vertex;

layout(location = 1) uniform mat4 mat;

out vec4 vertexColor;

void main() {
  gl_Position = mat * vec4(vertex.x, vertex.y, vertex.z, 1.0);
  vertexColor = gl_Position;
}