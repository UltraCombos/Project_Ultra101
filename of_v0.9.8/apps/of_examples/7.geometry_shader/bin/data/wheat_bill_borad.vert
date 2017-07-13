#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;
/*
in vec3 _wheat_swing;
in vec3 _wheat_angle;
in vec3 _wheat_color;
in vec3 _touch_swing;
*/

struct Wheat
{
	vec4 pos;
	vec4 angle;
	vec4 color;

	vec4 swing;
	vec4 touch_swing;
	float touch_theta;
	float touch_theta_v;
	float a;
	float b;	
};

layout(std430, binding=0) buffer _wheats_{
    Wheat _wheats[];
};

out block1
{
	vec3 _color;
	vec3 _angle;
	vec3 _swing;
	vec3 _touch;
} _out;
out vec4 ppp;
void main(void)
{
/*
	_out._color = _wheat_color;
	_out._angle = _wheat_angle;
	_out._swing = _wheat_swing;
	_out._touch = _touch_swing;
	*/
	_out._color = _wheats[gl_VertexID].color.xyz;
	_out._angle = _wheats[gl_VertexID].angle.xyz;
	_out._swing = _wheats[gl_VertexID].swing.xyz;
	_out._touch = _wheats[gl_VertexID].touch_swing.xyz;
	ppp = _wheats[gl_VertexID].pos;
	ppp.w = 1.0;
	gl_Position = ppp;
	
}