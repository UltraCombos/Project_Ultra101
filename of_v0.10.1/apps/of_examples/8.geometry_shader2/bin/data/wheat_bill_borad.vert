#version 410 core
#pragma include "perlin.glsl"
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;
layout (location = 4) in vec4 angle;

uniform float _max_swing_angle = 30;
uniform float _swing_pos_freq  = 0.1;
uniform float _swing_time_freq = 0.3;
uniform float _elapsed_time;
uniform float _max_root_angle;

out block1
{
	vec3 _color;
	vec3 _angle;
	vec3 _swing;
} _out;
vec3 _getUpDir(float x_rate, float z_rate, float max_degree)
{
	float max_radius = radians(max_degree);
	float h = 1.0 / tan(max_radius);
	if(max_degree == 0)
		return vec3(0);
	return normalize(vec3(x_rate, h, z_rate));
}
void main(void)
{
	vec3 scale_pos = position.xyz*_swing_pos_freq;
	float x_off = noise(scale_pos.x, scale_pos.z, _elapsed_time*_swing_time_freq, 0);
	float z_off = noise(scale_pos.x, scale_pos.z, 0, _elapsed_time*_swing_time_freq);

	vec3 up=vec3(0, 1, 0);
	vec3 dir = _getUpDir(x_off, z_off, _max_swing_angle);

	_out._angle = angle.xyz*_max_root_angle;
	_out._swing = cross(up,dir);
	
	_out._color = color.xyz* 0.7+0.5*(clamp(length(_out._swing)/radians(_max_swing_angle),0.0,1.0));	
	gl_Position = position;
	
}