//--------------------------------------------------
// File:    World.cpp
// Created: 28/01/2013 00:09:32
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"

#include "Global.h"
#include "World.h"
#include "Scene.h"
#include "Database/Player.h"
#include "Graphic/Camera/Camera.h"

void CWorld::Initialize()
{
	auto player = CPlayer::CreateObject();
	m_GameObjects.push_back(player);
	{
		auto newObj = make_shared<CFollowCamera>();
		player->SetCamera(newObj);
		Global::Scene().AddCameraToView(MAINGAME_VIEW, *newObj);
	}

	player->m_Position = glm::vec3(0, 0, 10);
}

void CWorld::Update()
{
	for_each(m_GameObjects.begin(), m_GameObjects.end(),
		[](shared_ptr<CBaseGameObject> it)
		{
			it->Update();
		});
}

// eof /////////////////////////////////////////////
