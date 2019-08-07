#version 400 core

uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec2 coord;
out gl_PerVertex {
	vec4 gl_Position;
};
void main()
{
	coord = texCoord;
	gl_Position = modelViewProjectionMatrix*position;
}
