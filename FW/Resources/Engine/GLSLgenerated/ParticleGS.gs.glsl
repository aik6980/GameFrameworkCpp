// layout (binding = 2) require 420
#version 420 core

// uniforms
layout (binding = 0) uniform CB00
{
	mat4x4 ViewXf;
	mat4x4 ProjectionXf;
	mat4x4 ViewIXf;
	mat4x4 ProjectionIXf;
	mat4x4 ViewProjectionIXf;
}CbViewCommon;

// stage input/output
in block
{
	vec4 Color0;
}IN[];

out block
{
	vec4 Texcoord0;
	vec4 Color0;	
}OUT;

// Specify the input and output primitive types, along
// with the maximum number of vertices that this shader
// might produce.
layout (lines) in;
layout (triangle_strip, max_vertices = 4)out;