#include "stdafx.h"
#include "ParticleManager.h"

#include "CoreCpp.h"
#include "Global.h"
#include "Graphic/GraphicCpp.h"

void CParticleManager::Initialize()
{
	// Load shaders
	m_ParticleSimShader = new CParticleSimComputeShader();
	m_ParticleSimShader->Load();

	// Initialize Particle Data
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		m_ParticleDeadList[i].Index = MAX_PARTICLES - 1 - i;
	}
}

void CParticleManager::Update()
{

}

void CParticleManager::SimulateEmitter(uint32_t id)
{
	float curr_time = Global::GameTimer().GetElapsedTime();
	CEmitter& emt = m_EmitterList[id];
	
	if (emt.EmissionRate != 0.0f)
	{
		while (emt.Accumulator > 1.0f)
		{
			emt.Accumulator -= 1.0f;
			uint32_t p_id = SpawnParticle();
			// initialize new particle
			if (p_id != INVALID_ID)
			{
				CParticle& particle = m_ParticleSpawnList[p_id];
				particle.Position_EmitterId = glm::vec4(emt.Position, id);
				particle.Begintime_Lifetime = glm::vec2(curr_time, emt.ParticleLifeTime);
				particle.Velocity = glm::normalize( glm::linearRand(glm::vec3(-0.5f, 1.0f, -0.5f), glm::vec3(0.5f, 1.0f, 0.5f)) );
			}
		}
	}
}

uint32_t CParticleManager::SpawnParticle()
{
	if (m_ParticleDeadCounter > 0)
	{
		// get new particle from the dead list
		ParticleDead& alive_p = m_ParticleDeadList[m_ParticleDeadCounter];
		m_ParticleDeadCounter--;

		return alive_p.Index;
	}
	else
	{
		Debug::Print(boost::wformat(TEXT("m_ParticleDeadCounter == 0, Cannot spawn any new particle")));
		return INVALID_ID;
	}
}
