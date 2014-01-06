#pragma once
#ifndef GeomCreator_h__
#define GeomCreator_h__

#include "RenderDevice/RenderDevice.h"

class CMeshData
{
public:

	vector<glm::vec3>			Positions;
	vector<glm::vec3>			Normals;
	vector<glm::vec3>			TangentUs;
	vector<glm::vec2>			UV0;
	
	Renderer::PrimitiveType		PrimType;
	vector<uint32_t>			Indices;

	void SetVertexData(uint32_t index, float px, float py, float pz, 
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v)
	{
		Positions[index] = glm::vec3(px, py, pz);
		Normals[index]	 = glm::vec3(nx, ny, nz);
		TangentUs[index] = glm::vec3(tx, ty, tz);
		UV0[index]		 = glm::vec2(u, v);
	}
};

template<class T>
class CMappedMeshData
{
public:
	vector<T>					Vertices;
	Renderer::PrimitiveType		PrimType;
	vector<uint32_t>			Indices;
};

class CGeomCreator
{
public:

	///<summary>
	/// Creates a box centered at the origin with the given dimensions.
	///</summary>
	void CreateBox(float width, float height, float depth, CMeshData& meshData);

	///<summary>
	/// Creates a sphere centered at the origin with the given radius.  The
	/// slices and stacks parameters control the degree of tessellation.
	///</summary>
	void CreateSphere(float radius, UINT sliceCount, UINT stackCount, CMeshData& meshData);

	///<summary>
	/// Creates an mxn grid in the xz-plane with m rows and n columns, centered
	/// at the origin with the specified width and depth.
	///</summary>
	void CreateGrid(float width, float depth, UINT m, UINT n, CMeshData& meshData);

	///<summary>
	/// Creates a quad covering the screen in NDC coordinates.
	/// Full screen, screen facing configuration
	///</summary>
	void CreateQuad(CMeshData& meshData);
};

#endif // GeomCreator_h__