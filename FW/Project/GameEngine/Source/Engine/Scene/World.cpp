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
	{
		CPlayer* newObj = CPlayer::CreateObject();
		m_GameObjects.push_back(newObj);
	}

	{
		CFreeCamera* newObj = new CFreeCamera();
		newObj->Position(glm::vec3(0,0,10));
		Global::Scene().AddCameraToView(MAINGAME_VIEW, *newObj);
	}
}

void CWorld::Update()
{
	for_each(m_GameObjects.begin(), m_GameObjects.end(),
		[](CBaseGameObject*	it)
		{
			it->Update();
		});
}

// eof /////////////////////////////////////////////
