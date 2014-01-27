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
#include "RigidBody.h"

class CParticle;
class CRigidBodyContactGenerator;
// type declarations (enum struct class) /////////
class CRigidBodyManager
{
public:
	CRigidBodyManager();

	void	BeginFrame();


	void		CreateSimulationGrid();
	void		CreateParticles(vector<CParticle>& particles, float size);
private:
	uint32_t	TotalNumVoxels()	{ return m_GridSize * m_GridSize * m_GridSize; }
	uint32_t	CalculateNumParticles(float size);

	list<CRigidBody>	m_RigidBodies;

	CRigidBodyContactGenerator*		m_ContactGenerator;

	float		m_WorldSize;
	float		m_VoxelSize; // smallest world unit that represented 1 particle
	uint32_t	m_NumParticlePerVoxel;

	uint32_t	m_GridSize;
	uint32_t	m_XStride, m_YStride, m_ZStride;

	vector<int32_t>		m_IndexArray;
	vector<int32_t>		m_CounterArray;
};

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RIGIDBODYSIMULATION_H__2014_01_12_23_40_15