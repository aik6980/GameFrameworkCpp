//--------------------------------------------------
// File:    GeomCreator.cpp
// Created: 08/04/2013 04:57:02
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "GeomCreator.h" 

void CGeomCreator::CreateQuad( CMeshData& meshData )
{
	const uint32_t numVerts = 4; 
	meshData.Positions.resize(numVerts);
	meshData.Normals.resize(numVerts);
	meshData.TangentUs.resize(numVerts);
	meshData.UV0.resize(numVerts);

	meshData.Indices.resize(6);

	// DirectX Coordinate system
	// mk:@MSITStore:C:\Program%20Files%20(x86)\Microsoft%20DirectX%20SDK%20(June%202010)\Documentation\DirectX9\windows_graphics.chm::/direct3d9/coordinate_systems.htm
	// Texture Coordinate
	// mk:@MSITStore:C:\Program%20Files%20(x86)\Microsoft%20DirectX%20SDK%20(June%202010)\Documentation\DirectX9\windows_graphics.chm::/direct3d9/texture_coordinates.htm
	// Position coordinates specified in NDC space.
	meshData.Positions[0]	= glm::vec3(-1.0f, -1.0f, 0.0f); 
	meshData.Normals[0]		= glm::vec3( 0.0f, 0.0f, -1.0f);
	meshData.TangentUs[0]	= glm::vec3( 1.0f, 0.0f, 0.0f );
	meshData.UV0[0]			= glm::vec2( 0.0f, 1.0f);

	meshData.Positions[1]	= glm::vec3(-1.0f, +1.0f, 0.0f); 
	meshData.Normals[1]		= glm::vec3( 0.0f, 0.0f, -1.0f);
	meshData.TangentUs[1]	= glm::vec3( 1.0f, 0.0f,  0.0f);
	meshData.UV0[1]			= glm::vec2( 0.0f, 0.0f);

	meshData.Positions[2]	= glm::vec3(+1.0f, +1.0f, 0.0f); 
	meshData.Normals[2]		= glm::vec3( 0.0f, 0.0f, -1.0f);
	meshData.TangentUs[2]	= glm::vec3( 1.0f, 0.0f,  0.0f);
	meshData.UV0[2]			= glm::vec2( 1.0f, 0.0f);

	meshData.Positions[3]	= glm::vec3(+1.0f, -1.0f, 0.0f); 
	meshData.Normals[3]		= glm::vec3( 0.0f, 0.0f, -1.0f);
	meshData.TangentUs[3]	= glm::vec3( 1.0f, 0.0f,  0.0f);
	meshData.UV0[3]			= glm::vec2( 1.0f, 1.0f);

	// OpenGL Convention (Right handed) - anti-clockwise (front)
	meshData.PrimType	= Renderer::PRIM_TRIANGLE;

	meshData.Indices[0] = 0;
	meshData.Indices[1] = 2;
	meshData.Indices[2] = 1;

	meshData.Indices[3] = 0;
	meshData.Indices[4] = 3;
	meshData.Indices[5] = 2;
}

void CGeomCreator::CreateSphere( float radius, UINT sliceCount, UINT stackCount, CMeshData& meshData )
{

}

void CGeomCreator::CreateGrid( float width, float depth, UINT m, UINT n, CMeshData& meshData )
{
	uint32_t vertexCount = m*n;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;

	float dx = width / (n-1);
	float dz = depth / (m-1);

	float du = 1.0f / (n-1);
	float dv = 1.0f / (m-1);

	meshData.Positions.resize(vertexCount);
	meshData.Normals.resize(vertexCount);
	meshData.TangentUs.resize(vertexCount);
	meshData.UV0.resize(vertexCount);

	for(UINT i = 0; i < m; ++i)
	{
		float z = halfDepth - i*dz;
		for(UINT j = 0; j < n; ++j)
		{
			float x = -halfWidth + j*dx;

			meshData.Positions[i*n+j]	= glm::vec3(x, 0.0f, z);
			meshData.Normals[i*n+j]		= glm::vec3(0.0f, 1.0f, 0.0f);
			meshData.TangentUs[i*n+j]	= glm::vec3(1.0f, 0.0f, 0.0f);

			// Stretch texture over grid.
			meshData.UV0[i*n+j].x = j*du;
			meshData.UV0[i*n+j].y = i*dv;
		}
	}

	//
	// Create the indices.
	//

	meshData.PrimType	 = Renderer::PRIM_TRIANGLE;
	uint32_t faceCount   = (m-1)*(n-1)*2; // triangles
	meshData.Indices.resize(faceCount*3); // 3 indices per face

	// Iterate over each quad and compute indices.
	UINT k = 0;
	for(UINT i = 0; i < m-1; ++i)
	{
		for(UINT j = 0; j < n-1; ++j)
		{
			meshData.Indices[k]   = i*n+j;
			meshData.Indices[k+1] = i*n+j+1;
			meshData.Indices[k+2] = (i+1)*n+j;

			meshData.Indices[k+3] = (i+1)*n+j;
			meshData.Indices[k+4] = i*n+j+1;
			meshData.Indices[k+5] = (i+1)*n+j+1;

			k += 6; // next quad
		}
	}
}

void CGeomCreator::CreateBox( float width, float height, float depth, CMeshData& meshData )
{
	//
	// Create the vertices.
	//

	const uint32_t numVerts = 24; 
	meshData.Positions.resize(numVerts);
	meshData.Normals.resize(numVerts);
	meshData.TangentUs.resize(numVerts);
	meshData.UV0.resize(numVerts);

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;
    
	// Fill in the front face vertex data.
	meshData.SetVertexData(0, -w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	meshData.SetVertexData(1, -w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	meshData.SetVertexData(2, +w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	meshData.SetVertexData(3, +w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	meshData.SetVertexData(4, -w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	meshData.SetVertexData(5, +w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	meshData.SetVertexData(6, +w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	meshData.SetVertexData(7, -w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	meshData.SetVertexData(8, -w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	meshData.SetVertexData(9, -w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	meshData.SetVertexData(10, +w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	meshData.SetVertexData(11, +w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	meshData.SetVertexData(12, -w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	meshData.SetVertexData(13, +w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	meshData.SetVertexData(14, +w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	meshData.SetVertexData(15, -w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	meshData.SetVertexData(16, -w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	meshData.SetVertexData(17, -w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	meshData.SetVertexData(18, -w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	meshData.SetVertexData(19, -w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	meshData.SetVertexData(20, +w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	meshData.SetVertexData(21, +w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	meshData.SetVertexData(22, +w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	meshData.SetVertexData(23, +w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
 
	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7]  = 5; i[8]  = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] =  9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	meshData.Indices.assign(&i[0], &i[36]);
}

