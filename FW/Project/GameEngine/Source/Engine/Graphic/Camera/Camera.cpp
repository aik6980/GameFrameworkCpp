//--------------------------------------------------
// File:    Camera.cpp
// Created: 29/03/2013 17:17:34
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "Camera.h"

#include "Core/CoreCpp.h"

CBaseCamera::CBaseCamera()
	: m_Fov(BasicMath::PI/4),
	m_ZNear(0.1f),
	m_ZFar(1000.0f),
	m_ProjectionMode(PERSPECTIVE),
	m_OrthographicHeight(20.0f)
{
	ZeroMemory(&m_ViewportDesc, sizeof(m_ViewportDesc));
	m_ViewportDesc.Width = Renderer::SCREEN_WIDTH;
	m_ViewportDesc.Height= Renderer::SCREEN_HEIGHT;

	// default:: set camera at the origin, looking down -z axis (OpenGL Convention)
	m_Position = glm::vec3(0,0,0);
	SetOrientation(glm::vec3(0,0,-1));
}

void CBaseCamera::SetOrientation( const glm::vec3& lookAt )
{
	glm::mat4 m = GeomMath::CreateLookAtMatrix(GeomMath::ORIGIN, lookAt);
	m = glm::inverse(m);
	
	m_Orientation = glm::quat(m);
}

glm::mat4 CBaseCamera::View() const
{
	glm::mat4 tx_inv = glm::translate(GeomMath::ORIGIN - m_Position);
	glm::mat4 rot_inv = glm::transpose(glm::toMat4(m_Orientation)); // rot_inv == rot_transpose

	return rot_inv *tx_inv;
}

glm::mat4 CBaseCamera::ViewInverse() const
{
	glm::mat4 m = glm::toMat4(m_Orientation);
	m[3] = glm::vec4(m_Position, 1.0f);
	return m;
}

glm::mat4 CBaseCamera::Projection() const
{
	float aspect = (float)m_ViewportDesc.Width/m_ViewportDesc.Height;
	switch(m_ProjectionMode)
	{
	case ORTHO:
		{
			float half_w = aspect * m_OrthographicHeight * 0.5f;
			float half_h = m_OrthographicHeight * 0.5f; 
			return glm::ortho(-half_w, half_w, -half_h, half_h, m_ZNear, m_ZFar);
		}
	case PERSPECTIVE:
	default:
		return GeomMath::CreateProjPerspective(m_Fov, aspect, m_ZNear, m_ZFar);
	}
}

glm::mat4 CBaseCamera::ViewProjection() const
{
	return View() * Projection();
}

glm::vec3 CBaseCamera::Forward() const
{
	glm::mat4 m = glm::toMat4(m_Orientation);
	// using OpenGL convention here, we are looking down -z axis (assuming we are looking into the screen, x-right y-up)
	return -glm::vec3(m[3]);
}
