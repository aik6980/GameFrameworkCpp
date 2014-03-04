//--------------------------------------------------
// File:    FreeCameraController.cpp
// Created: 29/03/2013 23:42:14
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "FreeCameraController.h"

#include "Core/CoreCpp.h"
#include "Global.h"
#include "Input/InputManager.h"

namespace
{
	float SPEED_SCALER		= 0.01f;
	float ANG_SPEED_SCALER	= 0.005f;
}

CFreeCameraController::CFreeCameraController()
: m_LinearSpeed(1.0f),
m_AngSpeed(0.1f)
{

}

void CFreeCameraController::Update()
{
	if(Global::InputManager().KeyDown('W'))
	{
		MoveForward();
	}
	else if(Global::InputManager().KeyDown('S'))
	{
		MoveBackward();
	}

	if (Global::InputManager().KeyDown('A'))
	{
		StrafeLeft();
	}
	else if (Global::InputManager().KeyDown('D'))
	{
		StrafeRight();
	}

	if (Global::InputManager().RightMouseDown())
	{
		MouseView();
	}
}

void CFreeCameraController::MoveForward()
{
	if (auto sp = m_Parent.lock())
	{
		const glm::vec3& v = GeomMath::Forward(glm::toMat4(sp->m_Orientation));
		sp->m_Position += v * m_LinearSpeed * SPEED_SCALER;
	}
}

void CFreeCameraController::MoveBackward()
{
	if (auto sp = m_Parent.lock())
	{
		const glm::vec3& v = GeomMath::Forward(glm::toMat4(sp->m_Orientation));
		sp->m_Position -= v * m_LinearSpeed * SPEED_SCALER;
	}
}

void CFreeCameraController::StrafeLeft()
{
	if (auto sp = m_Parent.lock())
	{
		const glm::vec3& v = GeomMath::Right(glm::toMat4(sp->m_Orientation));
		sp->m_Position -= glm::vec3(v[0], 0.0f, v[2]) * m_LinearSpeed * SPEED_SCALER;
	}
}

void CFreeCameraController::StrafeRight()
{
	if (auto sp = m_Parent.lock())
	{
		const glm::vec3& v = GeomMath::Right(glm::toMat4(sp->m_Orientation));
		sp->m_Position += glm::vec3(v[0], 0.0f, v[2]) * m_LinearSpeed * SPEED_SCALER;
	}
}

void CFreeCameraController::Pitch(float v)
{
	if (auto sp = m_Parent.lock())
	{
		// Decompose the current camera orientation
		const glm::mat4& m = glm::toMat4(sp->m_Orientation);
		const glm::vec3 right = GeomMath::Right(m);

		glm::quat rotQuat = glm::angleAxis(v, right);
		sp->m_Orientation = rotQuat * sp->m_Orientation;
	}
}

void CFreeCameraController::Yaw(float v)
{
	if (auto sp = m_Parent.lock())
	{
		glm::quat rotQuat = glm::angleAxis(v, GeomMath::UNIT_Y);
		sp->m_Orientation = rotQuat * sp->m_Orientation;
	}
}

void CFreeCameraController::MouseView()
{
	// if there's no velocity changed, skip the process
	glm::vec3 vel = Global::InputManager().CursorVelocity();
	if (glm::length2(vel) < glm::epsilon<float>() * glm::epsilon<float>())
		return;

	// find angular increment
	float angleYaw = vel.x * ANG_SPEED_SCALER;
	float anglePitch = vel.y * ANG_SPEED_SCALER;

	Yaw(-angleYaw);
	Pitch(-anglePitch);
}
