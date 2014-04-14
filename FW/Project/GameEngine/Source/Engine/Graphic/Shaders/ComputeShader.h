#ifndef ComputeShader_h__
#define ComputeShader_h__

#include "Core/Core.h"
#include "BaseShader.h"

class CParticleSimComputeShader : public CBaseComputeShader
{
public:
	CParticleSimComputeShader()
		: m_SSBOParticleList(0)
		, m_SSBOParticleDeadList(1)
		, m_SSBOParticleSortList(2)
		, m_AtomParticleCounter(0)
	{}

	enum eTechnique
	{
		PARTICLES_EMISSION,
		PARTICLES_SIMULATION
	};

	void Load();
	void Apply(eTechnique t);
private:
	void LoadTechnique(eTechnique t, const string& name);

	CGLSSBOView	m_SSBOParticleList;
	CGLSSBOView	m_SSBOParticleDeadList;
	CGLSSBOView	m_SSBOParticleSortList;

	CGLAtomicCounterView m_AtomParticleCounter; // both dead list counter/sorted list counter are binded at the same point
};

#endif // ComputeShader_h__
