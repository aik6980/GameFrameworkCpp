#pragma once
#ifndef Player_h__
#define Player_h__

#include "GameObject.h"
#include "Graphic/Camera/Camera.h"
#include "FreeCameraController.h"

#include "Graphic/Renderer/BaseRenderer.h"

class CPlayer : public CBaseGameObject
{
public:
	static shared_ptr<CPlayer> CreateObject();

	CPlayer();

	virtual void Update();

	void	SetCamera(shared_ptr<CBaseCamera> c) { m_PlayerControlCamera = c; }
private:
	shared_ptr<CBaseCamera>	m_PlayerControlCamera;
	CFreeCameraController	m_CameraController;
};

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
};

#endif // Player_h__