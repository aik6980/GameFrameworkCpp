#ifndef Particle_h__
#define Particle_h__

struct CParticle
{
	glm::vec4		Position_EmitterId;
	glm::vec3		Velocity;
	glm::vec2		Begintime_Lifetime;

	CParticle()
		: Position_EmitterId(0, 0, 0, 0),
		Velocity(0, 0, 0),
		Begintime_Lifetime(0, 0)
	{}
};

// using this for sorting and rendering
struct ParticleAlive
{
	glm::uint32		Index;
	glm::float32	Distance;

	ParticleAlive()
		: Index(0),
		Distance(0)
	{}
};

struct ParticleDead
{
	glm::uint32		Index;

	ParticleDead()
		: Index(0)
	{}
};

struct CEmitter
{
	glm::vec3		Position;
	glm::float32	EmissionRate;
	glm::float32	Accumulator;

	CEmitter()
		: Position(0, 0, 0),
		EmissionRate(0),
		Accumulator(0)
	{}
};

#endif // Particle_h__
