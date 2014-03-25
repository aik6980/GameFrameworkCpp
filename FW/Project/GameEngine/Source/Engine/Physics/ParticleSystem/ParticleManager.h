#ifndef ParticleManager_h__
#define ParticleManager_h__

#include "Particle.h"
#include "Graphic/Graphic.h"

class CParticleManager
{
public:
	CParticleManager() {}

	void	Initialize();
	void	Update();
private:
	const static uint32_t	MAX_EMITTERS	= 64 * 400;
	const static uint32_t	MAX_PARTICLES	= 256 * 4000;

	array<CParticle, MAX_PARTICLES>				m_ParticleList;
	array<ParticleAlive, MAX_PARTICLES>			m_ParticleAliveList;
	array<ParticleDead, MAX_PARTICLES>			m_ParticleDeadList;

	// GPU Program
	CParticleSimComputeShader*					m_ParticleSimShader;
};

#endif // ParticleManager_h__
