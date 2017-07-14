#version 430 core

uniform sampler2D _wheat_tex;
uniform float _fade_out_range;
uniform float _fade_in_range;

in float _dist_to_eye;
in vec2  _texCoord;
in vec4  _color;

out vec4 frag_color;

void main(void)
{
	float brightness=clamp((_dist_to_eye-_fade_in_range)/(_fade_out_range-_fade_in_range)+0.2,0.0,1.0);
	frag_color = brightness* _color * texture(_wheat_tex, _texCoord);
}
