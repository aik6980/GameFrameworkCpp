#include "stdafx.h"
#include "ParticleManager.h"

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
	CEmitter& emt = m_EmitterList[id];
	
	if (emt.EmissionRate != 0.0f)
	{
		if (emt.Accumulator > 1.0f)
		{

		}
	}
}

uint32_t CParticleManager::SpawnParticle()
{
	if (m_ParticleDeadCounter > 0)
	{
		// get new particle from the dead list
		ParticleDead& dead_p = m_ParticleDeadList[m_ParticleDeadCounter];
		m_ParticleDeadCounter--;
		// add to alive list
		ParticleAlive& alive_p = m_ParticleAliveList[m_ParticleAliveCounter];
		alive_p.Index = dead_p.Index;
		m_ParticleAliveCounter++;

		return alive_p.Index;
	}
	else
	{
		Debug::Print(boost::wformat(TEXT("m_ParticleDeadCounter == 0, Cannot spawn any new particle")));
		return -1;
	}
}
