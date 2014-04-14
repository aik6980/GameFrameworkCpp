#include "stdafx.h"
#include "ComputeShader.h"

#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Resource/ResourceManager.h" 

void CParticleSimComputeShader::Load()
{
	LoadTechnique(PARTICLES_EMISSION, "ParticleEmit.cs");
	LoadTechnique(PARTICLES_SIMULATION, "ParticleSimulation.cs");
}

void CParticleSimComputeShader::Apply(eTechnique t)
{
	switch (t)
	{
	case PARTICLES_SIMULATION:
		{
			m_ComputeTechniques[PARTICLES_SIMULATION]->Apply();

			m_SSBOParticleList.Bind();
			m_SSBOParticleDeadList.Bind();
			m_SSBOParticleSortList.Bind();
		}
		break;
	}
}

void CParticleSimComputeShader::LoadTechnique(eTechnique id, const string& name)
{
	CResourceObject* src = Global::ResourceManager().Get(GPUPROGRAM, name);
	if (src)
	{
		CGLComputeTechnique* t = new CGLComputeTechnique();
		t->SetName(name);
		t->Load(src->m_Path);

		m_ComputeTechniques.insert(make_pair(id, t));
	}
}
