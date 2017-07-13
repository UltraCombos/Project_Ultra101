#version 120

uniform sampler2D _wheat_tex;
uniform vec2  _tu;
uniform float _fade_out_range;
uniform float _fade_in_range;
varying float _dist_to_eye;
varying vec2  _texCoord;
//varying vec3  _color;

void main(void)
{
	float alpha=clamp((_dist_to_eye-_fade_in_range)/(_fade_out_range-_fade_in_range),0.0,1.0);
	gl_FragColor = alpha* gl_Color *texture2D(_wheat_tex, _texCoord*_tu);
}
