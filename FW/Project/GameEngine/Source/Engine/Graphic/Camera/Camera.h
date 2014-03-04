#pragma once
#ifndef Camera_h__
#define Camera_h__

#include "RenderDevice/RenderDevice.h"

class CBaseCamera
{
public:
	enum ProjectionMode
	{
		PERSPECTIVE,
		ORTHO,
	};

	CBaseCamera();

	glm::mat4	View() const;
	glm::mat4	ViewInverse() const;
	glm::mat4	Projection() const;
	glm::mat4	ViewProjection() const;

	void	SetOrientation(const glm::vec3& lookAt);
	
	void	Position(const glm::vec3& p)	{ m_Position = p; }
	void	Orientation(const glm::quat& q)	{ m_Orientation = q; }
private:
	glm::vec3		m_Position;
	glm::quat		m_Orientation;

	ProjectionMode			m_ProjectionMode;
	float					m_Fov;
	float					m_ZNear, m_ZFar;
	float					m_OrthographicHeight;
	Renderer::ViewportDesc	m_ViewportDesc;
};

class CFollowCamera : public CBaseCamera
{
public:
};

#endif // Camera_h__