//--------------------------------------------------
// File:    RigidBodySimulation.h
// Created: 12/01/2014 23:40:16
//
// Description: $
//

//--------------------------------------------------

#ifndef _RIGIDBODYSIMULATION_H__2014_01_12_23_40_15
#define _RIGIDBODYSIMULATION_H__2014_01_12_23_40_15

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "Core/Core.h"


class CRigidBody;
class CRigidBodyContactGenerator;
// type declarations (enum struct class) /////////
class CRigidBodyManager
{
public:
	void	BeginFrame();

private:
	list<CRigidBody>	m_RigidBodies;

	CRigidBodyContactGenerator*		m_ContactGenerator;
};

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RIGIDBODYSIMULATION_H__2014_01_12_23_40_15