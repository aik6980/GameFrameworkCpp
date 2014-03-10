// layout (binding = 2) require 420
#version 420 core
// common code

// input/output
layout (location = 0) in vec4 POSITION;
layout (location = 1) in vec4 COLOR;

out block
{
	vec4 Texcoord0;
	vec4 Color0;
}OUT;

void main()
{
	gl_Position = vec4(POSITION.xyz, 1.0);
	OUT.Color0	= COLOR;
}