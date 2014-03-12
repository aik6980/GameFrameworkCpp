#include "stdafx.h" 
#include "VFXSystem.h"

#include "Global.h"
#include "Input/InputManager.h"
#include "RenderDevice/RenderDeviceCpp.h"

#include "Scene/Scene.h"
#include "Graphic/Renderer/SpriteRenderer.h"

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
m_SegmentLifetime(1.0f),
m_AccumDistance(0.0f)
{
	m_ParticleList.reserve(16);

	glm::vec3 cursorPos = Global::InputManager().CursorPosition();
	glm::vec2 vp_size = Global::Renderer().BackBufferSize();
	cursorPos[0] = (cursorPos[0] / vp_size.x) * 2.0f - 1.0f;
	cursorPos[1] = (1.0f - cursorPos[1] / vp_size.y) * 2.0f - 1.0f;
	m_LastSpawnedPosition = cursorPos;
}

void CRibbonTrail::Update()
{
	float gameTime = Global::GameTimer().GetElapsedTime();
	glm::vec2 vp_size = Global::Renderer().BackBufferSize();

	glm::vec3 delta_pos = Global::InputManager().CursorVelocity();
	delta_pos[0] = (delta_pos[0] / vp_size.x) * 2.0f;
	delta_pos[1] = (delta_pos[1] / vp_size.y) * 2.0f;
	m_AccumDistance += glm::length2(delta_pos);

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

	if (m_AccumDistance > m_SegmentLength * m_SegmentLength)
	{
		ParticleData p;

		glm::vec3 cursorPos = Global::InputManager().CursorPosition();
		cursorPos[0] = (cursorPos[0] / vp_size.x) * 2.0f - 1.0f;
		cursorPos[1] = (1.0f - cursorPos[1] / vp_size.y) * 2.0f - 1.0f;

		p.Position = cursorPos;
		p.BeginTime = gameTime;
		p.Lifetime = m_SegmentLifetime;

		if (m_ParticleList.size() > m_MaxNumSegments - 1)
		{
			m_ParticleList.front().Lifetime = 0;
		}

		m_ParticleList.push_back(p);
		m_AccumDistance = 0;
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
