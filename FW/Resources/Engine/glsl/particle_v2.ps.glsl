// layout (binding = 2) require 420
#version 420 core

// uniforms

// stage input/output
in block
{
	vec4 Texcoord0;
	vec4 Color0;	
}IN;

out vec4 COLOR;

void main()
{
	COLOR = vec4(IN.Color0.xyz, 1);
}