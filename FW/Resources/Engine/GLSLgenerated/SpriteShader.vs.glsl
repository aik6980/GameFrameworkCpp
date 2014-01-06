// layout (binding = 2) require 420
#version 420 core
// common code

// vertex shader code
layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec2 TEXCOORD0;
layout (location = 2) in vec4 INST_POSITION;
layout (location = 3) in vec4 INST_COLOR;

out block
{
	vec4 TexCoord0;
	vec4 Color0;
}OUT;

// uniforms
layout (binding = 2) uniform CB02
{
	vec4 Offset;
}Cb02;

void main()
{
	vec3 position	= POSITION.xyz * INST_POSITION.w + vec3(INST_POSITION.xyz + Cb02.Offset.xyz);
	gl_Position 	= vec4(position, 1.0);
	OUT.TexCoord0	= vec4(TEXCOORD0, 0, 0);
	OUT.Color0		= INST_COLOR;
}
