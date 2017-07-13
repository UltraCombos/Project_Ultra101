#version 430 core
#pragma include "perlin.glsl"
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

uniform float _elapsed_time;
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
vec3 _getUpDir(float x_rate, float z_rate, float max_degree)
{
	float max_radius = radians(max_degree);
	float h = 1.0 / tan(max_radius);
	return normalize(vec3(x_rate, h, z_rate));
}
void main(void)
{
	float swing_freq = 0.5;
	float x_off = noise(_wheats[gl_VertexID].pos.x, _wheats[gl_VertexID].pos.z, _elapsed_time*swing_freq, 0);
	float z_off = noise(_wheats[gl_VertexID].pos.x, _wheats[gl_VertexID].pos.z, 0, _elapsed_time*swing_freq);

	vec3 up=vec3(0, 1, 0);
	vec3 dir = _getUpDir(x_off, z_off, 30);
	
	_out._color = _wheats[gl_VertexID].color.xyz;
	_out._angle = _wheats[gl_VertexID].angle.xyz;
	_out._swing = cross(up,dir);//_wheats[gl_VertexID].swing.xyz;
	_out._touch = _wheats[gl_VertexID].touch_swing.xyz;	
	gl_Position = _wheats[gl_VertexID].pos;
	
}