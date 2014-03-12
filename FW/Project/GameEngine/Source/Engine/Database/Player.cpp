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
#include "RenderDevice/RenderDeviceCpp.h"

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
