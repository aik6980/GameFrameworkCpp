#ifndef	PARTICLE_SHARED_GLSL
#define	PARTICLE_SHARED_GLSL

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


#endif