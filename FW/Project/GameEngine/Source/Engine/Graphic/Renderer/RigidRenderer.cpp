// local includes //////////////////////////////////
#include "stdafx.h" 
#include "RigidRenderer.h" 

#include "Core/CoreCpp.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Global.h"

void CRigidRenderer::Render( CGLDevice& context, RenderViewID currView )
{
	static float t = 0;
	static glm::quat orient(0,0,0,1);

	t=Global::GameTimer().GetFrameTime();

	glm::quat rot_x = glm::angleAxis(t, GeomMath::UNIT_Y);
	glm::quat rot_y = glm::angleAxis(t, GeomMath::UNIT_Y);
	glm::quat rot_z = glm::angleAxis(t, GeomMath::UNIT_Z);

	orient = rot_z * rot_y * rot_x * orient;
	m_InstanceData[0].Rotation = glm::vec4(orient.x, orient.y, orient.z, orient.w);
	m_InstanceVB.SetData(m_InstanceData);

	switch(currView)
	{
	case MAINGAME_VIEW:
		{
			// for all the meshes

			// update the vb/ib

			// update per-object constant buffer

			// update the render pipeline
			m_Effect->SetCurrTech(CRigidShader::MAIN_INSTANCING);
			m_Effect->Apply();

			// draw call
			m_PosVB.SetBuffer();
			m_Tex0VB.SetBuffer();
			m_InstanceVB.SetBuffer();
			m_IB.DrawInstancing(m_InstanceData.size());
		}
		break;
	}
}

void CRigidRenderer::Init()
{
	m_Effect= new CRigidShader();
	m_Effect->Load();
	
	CMeshData meshData;
	CGeomCreator geomCreator;
	geomCreator.CreateBox(1,1,1,meshData);

	m_PosVB.InputSlot(0);
	m_PosVB.SetData(meshData.Positions);
	m_Tex0VB.InputSlot(1);
	m_Tex0VB.SetData(meshData.UV0);

	m_IB.SetData(meshData.Indices);

	// InstanceData
	{
		CRigidShader::INSTANCE_DATA inst_data[] = 
		{
			{ glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1) },
		};

		copy(inst_data, inst_data + 1, back_inserter(m_InstanceData));
		m_InstanceVB.InputSlot(2);
		m_InstanceVB.BufferUsage(DYNAMIC_DRAW);
		m_InstanceVB.SetData(m_InstanceData);
	}
}


