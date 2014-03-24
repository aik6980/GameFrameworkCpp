#pragma once
#ifndef VFXSystem_h__
#define VFXSystem_h__

#include "GameObject.h"
#include "Graphic/Renderer/BaseRenderer.h"

struct ParticleData
{
	glm::vec3	Position;
	float		Lifetime;
	float		BeginTime;

	bool		Alive(float t)	{ return (DeathTime() - t) > 0.0f; }
	float		DeathTime()		{ return BeginTime + Lifetime; }
};

class CRibbonTrail : public CBaseGameObject, public CGameObjectRenderInterface
{
public:
	static shared_ptr<CRibbonTrail> CreateObject();

	CRibbonTrail();

	virtual void Update();
	virtual void PreRender(CGLDevice& context, RenderViewID currView, RendererID currRenderer);
private:
	// Ribbon information
	uint32_t	m_MaxNumSegments;
	float		m_SegmentLength;
	float		m_SegmentLifetime;

	// Particle List
	vector<ParticleData>	m_ParticleList;

	// Simulation State
	glm::vec3	m_LastSpawnedPosition;
	float		m_AccumDistance;
};

class CSimpleParticleSystem : public CBaseGameObject
{
public:
	static shared_ptr<CSimpleParticleSystem> CreateObject();

	virtual void Update();
private:

};

#endif // VFXSystem_h__
