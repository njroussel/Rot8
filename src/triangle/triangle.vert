#version 460 core

layout(location = 0) in vec3 vertex;

out vec4 vertexColor;

void main() {
  gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
  vertexColor = gl_Position;
}