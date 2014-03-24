//--------------------------------------------------
// File:    RigidBody.h
// Created: 13/01/2014 00:06:44
//
// Description: $
//

//--------------------------------------------------

#ifndef _RIGIDBODY_H__2014_01_13_00_06_44
#define _RIGIDBODY_H__2014_01_13_00_06_44

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core/Core.h"
#include "Particle.h"

// type declarations (enum struct class) /////////
class CRigidBody
{
public:
	CRigidBody();

	void	ClearAccumulator();
private:
	// Particle representation
	void	CreateParticles();

	// Basic Dynamic
	glm::vec3	m_Position;
	glm::vec3	m_Velocity;

	// Particle representation
	// default as a cube
	float		m_Size;

	vector<CRigidParticleProxy>	m_Particles;
};

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RIGIDBODY_H__2014_01_13_00_06_44