#version 400 core
layout(location = 0) out vec4 fragColor;

in vec2 coord;
uniform sampler2DRect pos_tex;
uniform sampler2DRect vel_tex;
uniform float noise;
void main()
{
  vec4 _pos = texture(pos_tex, coord);
  vec4 _vel = texture(vel_tex, coord);
  //_pos = _pos + _vel;
  fragColor = vec4(_pos.xyz+_vel.xyz,1.0);
/*
  if(coord.x > 512)
  fragColor = vec4(1,0,0,1);
  else
  fragColor = vec4(0,1,0,1);
*/
}
