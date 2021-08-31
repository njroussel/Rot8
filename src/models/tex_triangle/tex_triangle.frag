#version 460 core

in vec2 texCoord;

out vec4 fragColor;

layout(location = 0) uniform vec4 color;
layout(location = 1) uniform sampler2D tex;

void main() {
  vec4 texColor = texture(tex, texCoord);

  vec4 inputColor = vec4(color.rgb, color.a / 2);
  texColor.a = texColor.a / 2;

  fragColor = inputColor + texColor;
}