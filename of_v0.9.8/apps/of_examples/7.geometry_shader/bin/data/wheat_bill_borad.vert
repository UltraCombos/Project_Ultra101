#version 400

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

in vec3 _wheat_swing;
in vec3 _wheat_angle;
in vec3 _wheat_color;
in vec3 _touch_swing;

out block1
{
	vec3 _color;
	vec3 _angle;
	vec3 _swing;
	vec3 _touch;
} _out;

void main(void)
{
	_out._color = _wheat_color;
	_out._angle = _wheat_angle;
	_out._swing = _wheat_swing;
	_out._touch = _touch_swing;
	gl_Position = position;
}