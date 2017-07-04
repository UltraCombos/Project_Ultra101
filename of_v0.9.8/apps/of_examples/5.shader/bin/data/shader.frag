#version 400 core
layout(location = 0) out vec4 fragColor;
in vec2 coord;
uniform sampler2DRect tex;
uniform int colorMode;
void main()
{
	if(length(coord - 0.5*textureSize(tex)) > 0.5*textureSize(tex).y)
		discard;
		
	vec4 color = texture(tex,coord);	
	switch(colorMode)
	{
		case 1:
		fragColor = color;
	break;
		case 2:		
		fragColor = color.bgra;
	break;
		case 3:
		//float gray = color.r*0.299+color.g*0.587 + color.b*0.114;
		float gray = dot(color.rgb,vec3(0.299,0.587,0.114));
		fragColor = vec4(vec3(gray),1.0);
	break;
		case 4:
		fragColor = vec4(vec3(color.r, 0.0, 0.0), 1.0);
	break;
		case 5:
		fragColor = vec4(vec3(0.0, color.g, 0.0), 1.0);
	break;
		case 6:
		fragColor = vec4(vec3(0.0, 0.0, color.b), 1.0);
	break;
	}

}