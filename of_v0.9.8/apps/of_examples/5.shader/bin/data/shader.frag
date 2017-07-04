#version 430 core
layout(location = 0) out vec4 fragColor;
in vec2 coord;
uniform sampler2DRect tex;
void main()
{
	fragColor = texture(tex,coord);
}