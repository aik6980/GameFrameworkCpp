#include "stdafx.h"
#include "RigidBodySimulation.h"

CRigidBodyManager::CRigidBodyManager()
	: m_WorldSize(128.0f),
	m_VoxelSize(1.0f),
	m_NumParticlePerVoxel(4)
{

}

void CRigidBodyManager::CreateSimulationGrid()
{
	// calculate grid size
	m_GridSize = (uint32_t)ceil(m_WorldSize/m_VoxelSize);
	// 2 extra voxels in case particles go slightly outside the world
	m_GridSize += 2;

	// precalculate strides (using for quick access data in our voxel array)
	m_XStride = m_GridSize * m_GridSize;
	m_YStride = m_GridSize;
	m_ZStride = 1;

	// initialize our data structure
	uint32_t numVoxels = TotalNumVoxels();
	m_IndexArray.clear();
	m_IndexArray.resize(numVoxels * m_NumParticlePerVoxel, -1);

	m_CounterArray.clear();
	m_CounterArray.resize(numVoxels, 0);
}

uint32_t CRigidBodyManager::CalculateNumParticles( float size )
{
	return (uint32_t)ceil(size/m_VoxelSize);
}

void CRigidBodyManager::CreateParticles( vector<CParticle>& particles, float size )
{
	uint32_t numParticlesPerSize = CalculateNumParticles(size);
	// allocate particles
	particles.resize(numParticlesPerSize * numParticlesPerSize * numParticlesPerSize);

	uint32_t i = 0;
	for(uint32_t u=0; u<numParticlesPerSize; ++u)
		for(uint32_t v=0; v<numParticlesPerSize; ++v)
			for(uint32_t w=0; w<numParticlesPerSize; ++w)
			{
				// scale particle init position to fit inside our object voxelized AABB
				float x = (2*(float)u/numParticlesPerSize - 1) * numParticlesPerSize/2.0f * m_VoxelSize;
				float y = (2*(float)v/numParticlesPerSize - 1) * numParticlesPerSize/2.0f * m_VoxelSize;
				float z = (2*(float)w/numParticlesPerSize - 1) * numParticlesPerSize/2.0f * m_VoxelSize;

				particles[i].m_Position = glm::vec3(x, y, z);
				// next particle
				++i;
			}
}
