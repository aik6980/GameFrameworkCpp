#pragma once
#ifndef Player_h__
#define Player_h__

#include "GameObject.h"
#include "Graphic/Camera/Camera.h"
#include "FreeCameraController.h"

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

#endif // Player_h__