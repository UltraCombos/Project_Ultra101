#version 120
attribute vec3 _wheat_swing;
attribute vec3 _wheat_angle;
attribute vec3 _wheat_color;
attribute vec3 _touch_swing;

varying   vec3 _color;
varying   vec3 _angle;
varying   vec3 _swing;
varying   vec3 _touch;


void main(void)
{
	
	_color = _wheat_color;
	_angle = _wheat_angle;
	_swing = _wheat_swing;
	_touch = _touch_swing;
	gl_Position = gl_Vertex;
}