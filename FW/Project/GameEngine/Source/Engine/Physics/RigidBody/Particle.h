#ifndef RigidParticle_h__
#define RigidParticle_h__

#include "Core/Core.h"

class CRigidParticleProxy
{
public:
	// Basic
	glm::vec3	m_Position;
	glm::vec3	m_Velocity;
	
	glm::vec3	m_Force;
	float		m_Mass;

	// Grid Registration
	glm::i32vec3	m_GridIndex;
	int32_t			m_ParticleIndex;
private:
};


#endif // RigidParticle_h__
