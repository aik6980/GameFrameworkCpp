#pragma once
#ifndef FreeCameraController_h__
#define FreeCameraController_h__

#include "GameObject.h"

class CFreeCameraController
{
public:
	CFreeCameraController();

	void	SetParent(shared_ptr<CBaseGameObject> obj) { m_Parent = obj; }

	void	Update();
private:
	void	MoveForward();
	void	MoveBackward();
	void	StrafeLeft();
	void	StrafeRight();

	void	MouseView();
	void	Pitch(float v);
	void	Yaw(float v);


	weak_ptr<CBaseGameObject> m_Parent;
	float	m_LinearSpeed;
	float	m_AngSpeed;
};

#endif // FreeCameraController_h__