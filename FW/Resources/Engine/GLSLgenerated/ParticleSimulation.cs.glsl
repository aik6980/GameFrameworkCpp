// layout (binding = 2) requires 420
// compute shader requires 430
#version 430 core

// uniforms
layout (binding = 0) uniform CB00
{
	float	gameTime;
}CbSceneCommon;

// buffers
struct EmitterConst
{
	
};

struct ParticleSimData
{
	vec3	pos;
	vec3	vel;
	vec4	lifetime;
};

layout (std430, binding = 1) buffer
{
	ParticleSimData p[];
} g_input_data;

// Input layout qualifier declaring a 16x 16(x 1)local
// workgroup size
layout (local_size_x =16, local_size_y = 16) in;
void main()
{
	//Do nothing.
}