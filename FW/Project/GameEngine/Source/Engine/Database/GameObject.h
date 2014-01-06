#pragma once
#ifndef GameObject_h__
#define GameObject_h__

#include "Core/Core.h"

class CBaseGameObject
{
public:
	virtual void Update()=0;
	
	glm::vec3	m_Position;
	glm::quat	m_Orientation;
};

#endif // GameObject_h__