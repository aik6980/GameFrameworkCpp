// layout (binding = 2) require 420
// SSBO requires 430
#version 430 core

#include "particle.inc.glsl"

// input/output
layout (location = 0) in uint 	ID;
layout (location = 1) in float 	DISTANCE;

#include "particle.inc.glsl"

out block
{
	vec4 Color0;
}OUT;

void main()
{
	// get particle data from buffer
	Particle particle = g_ParticleInstances.Data[ID];

	gl_Position = vec4(particle.Position_Id.xyz, 1.0);
	OUT.Color0	= vec4(1.0, 0.0, 1.0, 1.0);
}