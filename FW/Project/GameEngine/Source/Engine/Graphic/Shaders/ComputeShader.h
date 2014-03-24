#ifndef ComputeShader_h__
#define ComputeShader_h__

#include "Core/Core.h"
#include "BaseShader.h"

class CParticleSimComputeShader : public CBaseComputeShader
{
public:
	enum eTechnique
	{
		PARTICLES_EMISSION,
		PARTICLES_SIMULATION
	};

	void Load();
	void Apply(eTechnique t);
private:
	void LoadTechnique(eTechnique t, const string& name);
};

#endif // ComputeShader_h__
