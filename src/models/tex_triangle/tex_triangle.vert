#version 460 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;

out vec2 texCoord;

void main() {
  texCoord = vTexCoord;
  gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
}