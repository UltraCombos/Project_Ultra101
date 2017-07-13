#version 400

uniform sampler2D _wheat_tex;
uniform vec2  _tu;
uniform float _fade_out_range;
uniform float _fade_in_range;
in float _dist_to_eye;
in vec2  _texCoord;
in vec4 _color;

out vec4 frag_color;
//varying vec3  _color;

void main(void)
{
	float alpha=clamp((_dist_to_eye-_fade_in_range)/(_fade_out_range-_fade_in_range),0.0,1.0);
	frag_color = alpha* _color * texture(_wheat_tex, _texCoord*_tu);
}
