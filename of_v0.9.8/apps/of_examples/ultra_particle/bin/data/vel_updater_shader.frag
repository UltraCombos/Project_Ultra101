#version 400 core
layout(location = 0) out vec4 fragColor;

in vec2 coord;
uniform sampler2DRect pos_tex;
uniform sampler2DRect vel_tex;
uniform float force;
uniform float max_vel;

ivec2 tex_size = ivec2(textureSize(pos_tex));
int len = tex_size.x*tex_size.y;
void main()
{
  vec3 _pos = texture(pos_tex, coord).xyz;
  vec3 _vel = texture(vel_tex, coord).xyz;

  vec3 avg_pos = vec3(0);
#if 0
  for(int y=0;y<tex_size.y;++y)
  {
    for(int x=0;x<tex_size.x;++x)
    {
      avg_pos += texture(pos_tex, vec2(x,y)+0.5).xyz;
    }
  }
  avg_pos/=float(len);
#endif
  vec3 dir = avg_pos - _pos;
  float dist = length(dir);
  dir /= dist;



   _vel = _vel + force*dir * pow(1.0/dist,2);
  
   if(length(_vel)>max_vel)
   {
     _vel=normalize(_vel)*max_vel;
   }

  //_pos = _pos + _vel;
  fragColor = vec4(_vel.xyz,1.0);
/*
  if(coord.x > 512)
  fragColor = vec4(1,0,0,1);
  else
  fragColor = vec4(0,1,0,1);
*/
}
