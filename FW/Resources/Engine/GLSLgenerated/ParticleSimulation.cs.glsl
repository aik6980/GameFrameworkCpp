// layout (binding = 2) requires 420
// compute shader requires 430
#version 430 core

// uniforms
layout (binding = 1) uniform CB01
{
	vec4	GameTimerData;
}CbSceneCommon;

float CurrentTime()
{
	return CbSceneCommon.GameTimerData.x;
}

float DeltaTime()
{
	return CbSceneCommon.GameTimerData.y;
}

// buffers
struct Particle
{
	vec4	Position_Id;
	vec3	Velocity;
	vec2	Begintime_Lifetime;
};

layout (std430, binding = 0) buffer SSBO00 
{
	Particle p[];
} g_input_data;

// Input layout qualifier declaring a 16x 16(x 1)local
// workgroup size
layout (local_size_x =16) in;
void main()
{
	int pid = 
}
