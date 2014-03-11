//--------------------------------------------------
// File:    Player.cpp
// Created: 29/03/2013 20:34:42
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "Player.h"

#include "Global.h"
#include "Input/InputManager.h"

#include "Scene/Scene.h"
#include "Graphic/Renderer/SpriteRenderer.h"

shared_ptr<CPlayer> CPlayer::CreateObject()
{
	auto obj = make_shared<CPlayer>();
	obj->m_CameraController.SetParent(obj);

	// register with sub systems

	return obj;
}

CPlayer::CPlayer()
{

}

void CPlayer::Update()
{
	m_CameraController.Update();
	m_PlayerControlCamera->Position(m_Position);
	m_PlayerControlCamera->Orientation(m_Orientation);
}


shared_ptr<CRibbonTrail> CRibbonTrail::CreateObject()
{
	auto obj = make_shared<CRibbonTrail>();

	CSpriteRenderer* renderer = Global::Scene().GetRenderer<CSpriteRenderer>(SPRITE_RENDERER);
	renderer->RegisterGameObject(obj);

	return obj;
}

CRibbonTrail::CRibbonTrail() :
m_MaxNumSegments(16),
m_SegmentLength(0.1f),
m_SegmentLifetime(1.0f)
{
	m_ParticleList.reserve(16);
}

void CRibbonTrail::Update()
{
	float gameTime = Global::GameTimer().GetElapsedTime();
	glm::vec3 cursorPos = Global::InputManager().CursorPosition();
	
	cursorPos[0] = (cursorPos[0] / Renderer::SCREEN_WIDTH) * 2.0f - 1.0f;
	cursorPos[1] = (1.0f - cursorPos[1] / Renderer::SCREEN_HEIGHT) * 2.0f - 1.0f;

	// kill any death particles
	for (uint32_t i = 0; i < m_ParticleList.size(); ++i)
	{
		ParticleData& p = m_ParticleList[i];
		if (!p.Alive(gameTime))
		{
			p = m_ParticleList.back();
			m_ParticleList.pop_back();
		}
	}

	if (glm::length2(cursorPos - m_LastSpawnedPosition) > m_SegmentLength * m_SegmentLength)
	{
		ParticleData p;
		p.Position = cursorPos;
		p.BeginTime = gameTime;
		p.Lifetime = m_SegmentLifetime;

		if (m_ParticleList.size() > m_MaxNumSegments - 1)
		{
			m_ParticleList.front().Lifetime = 0;
		}

		m_ParticleList.push_back(p);
		m_LastSpawnedPosition = cursorPos;
	}
}

void CRibbonTrail::PreRender(CGLDevice& context, RenderViewID currView, RendererID currRenderer)
{
	CSpriteRenderer* renderer = Global::Scene().GetRenderer<CSpriteRenderer>(currRenderer);

	std::sort(m_ParticleList.begin(), m_ParticleList.end(), 
		[](ParticleData& a, ParticleData& b)
		{
			return a.BeginTime < b.BeginTime;
		});

	for (uint32_t i = 0; i < m_ParticleList.size(); ++i)
	{
		VFXVertex v;
		v.Position = glm::vec4(m_ParticleList[i].Position, 1.0f);
		v.Color = glm::vec4(0.75f, 0.5f, 0.5f, 1.0f);

		renderer->AddInstanceData(v);
	}
}
