#ifndef ParticleManager_h__
#define ParticleManager_h__

#include "Particle.h"
#include "Graphic/Graphic.h"

class CParticleManager
{
public:
	CParticleManager() 
	: m_ParticleAliveCounter(0),
	m_ParticleDeadCounter(MAX_PARTICLES - 1)
	{}

	void	Initialize();
	void	Update();
private:
	uint32_t	SpawnParticle();
	void		SimulateEmitter(uint32_t id);

	const static uint32_t	MAX_EMITTERS	= 64 * 400;
	const static uint32_t	MAX_PARTICLES	= 256 * 4000;

	array<CEmitter, MAX_EMITTERS>				m_EmitterList;

	array<CParticle, MAX_PARTICLES>				m_ParticleList;

	uint32_t									m_ParticleAliveCounter;
	array<ParticleAlive, MAX_PARTICLES>			m_ParticleAliveList;
	uint32_t									m_ParticleDeadCounter;
	array<ParticleDead, MAX_PARTICLES>			m_ParticleDeadList;

	// GPU Program
	CParticleSimComputeShader*					m_ParticleSimShader;
};

#endif // ParticleManager_h__
