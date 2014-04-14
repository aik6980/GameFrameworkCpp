// layout (binding = 2) require 420
// SSBO requires 430
#version 430 core
// common code

// buffer
struct Particle
{
	vec4	Position_Id;
	vec3	Velocity;
	vec2	Begintime_Lifetime;
};

layout (std430, binding = 0) buffer SSBO00 
{
	Particle Data[];
} g_ParticleInstances;

// input/output
layout (location = 0) in uint 	ID;
layout (location = 1) in float 	DISTANCE;

out block
{
	vec4 Color0;
}OUT;

void main()
{
	// get particle data from buffer
	Particle particle = g_ParticleInstances.Data[ID];

	gl_Position = vec4(particle.Position.xyz, 1.0);
	OUT.Color0	= vec4(1.0, 0.0, 1.0, 1.0);
}