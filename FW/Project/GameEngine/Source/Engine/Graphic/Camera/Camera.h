#pragma once
#ifndef Camera_h__
#define Camera_h__

#include "RenderDevice/RenderDevice.h"

class CBaseCamera
{
public:
	CBaseCamera();

	glm::mat4	View() const;
	glm::mat4	ViewInverse() const;
	glm::mat4	Projection() const;
	glm::mat4	ViewProjection() const;

	glm::vec3	Forward() const;

	void	SetOrientation(const glm::vec3& lookAt);
	void	Position(const glm::vec3& p)	{ m_Position = p; } 
private:
	glm::vec3		m_Position;
	glm::quat		m_Orientation;

	float					m_Fov;
	float					m_ZNear, m_ZFar;
	Renderer::ViewportDesc	m_ViewportDesc;
};

class CFreeCamera : public CBaseCamera
{
public:
	void MoveForward();
	void MoveBackward();
	void StrafeLeft();
	void StrafeRight();
	void MouseLook();

	float	m_MoveSpeed;
	float	m_MouseSpeed;
private:
};

#endif // Camera_h__