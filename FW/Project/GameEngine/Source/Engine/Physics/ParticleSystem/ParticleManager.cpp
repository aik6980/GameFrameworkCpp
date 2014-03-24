#include "stdafx.h"
#include "ParticleManager.h"

#include "Graphic/GraphicCpp.h"

void CParticleManager::Initialize()
{
	m_ParticleSimShader = new CParticleSimComputeShader();
	m_ParticleSimShader->Load();
}

void CParticleManager::Update()
{

}
