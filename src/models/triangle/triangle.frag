#version 460 core

in vec4 vertexColor;

out vec4 FragColor;

layout(location = 0) uniform vec4 tmpColor;

void main() { FragColor = tmpColor; }