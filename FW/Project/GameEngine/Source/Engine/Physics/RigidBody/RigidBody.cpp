// OS includes /////////////////////////////////////
#include "stdafx.h"
// local includes //////////////////////////////////
#include "RigidBody.h" 

#include "Core/CoreCpp.h"
#include "Global.h"
#include "RigidBodySimulation.h"

CRigidBody::CRigidBody()
	: m_Size(3)
{

}

void CRigidBody::ClearAccumulator()
{
	Debug::Print("need implementation");
}

void CRigidBody::CreateParticles()
{
	Global::RigidBodyManager().CreateParticles(m_Particles, m_Size);
}
