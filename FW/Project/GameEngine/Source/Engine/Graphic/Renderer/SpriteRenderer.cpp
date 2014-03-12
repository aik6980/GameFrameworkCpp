//--------------------------------------------------
// File:    SpriteRenderer.cpp
// Created: 31/03/2013 13:53:23
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "SpriteRenderer.h" 
#include "RenderDevice/RenderDeviceCpp.h"

#include "Global.h"

float g_offset = 
	-0.25;

void CSpriteRenderer::PreRender(CGLDevice& context, RenderViewID currView)
{
	m_VFXVertexData.clear();

	CBaseRenderer::PreRender(context, currView);

	m_VFXVertexDataVB.SetData(m_VFXVertexData);
}

void CSpriteRenderer::Render( CGLDevice& context, RenderViewID currView )
{
	switch(currView)
	{
	case MAINGAME_VIEW:
		{
			// for all the meshes

			// update the vb/ib

			// update per-object constant buffer
			//m_Effect->m_CbObjectCommon.m_Data.WorldXf = glm::scale( glm::vec3(0.5f, 0.5f, 0.5f));
			CSpriteShader::CB02 cb02;
			cb02.Offset = glm::vec4(0,0,g_offset,0);
			m_Effect->m_CB02.SetData(cb02);
			//m_Effect->m_TexDiffuse.SetResource(m_TexDiffuse->GetSRV(context));

			// update the render pipeline
			m_Effect->SetCurrTech(CSpriteShader::MAIN_INSTANCING);
			m_Effect->Apply();

			// draw call
			m_PosVB.SetBuffer();
			m_Tex0VB.SetBuffer();
			//m_IB.Draw(context);
			m_InstanceVB.SetBuffer();
			m_IB.DrawInstancing(m_InstanceData.size());

			m_VFXRibbonEffect->SetCurrTech(CVFXRibbonShader::MAIN);
			m_VFXRibbonEffect->Apply();
			
			m_VFXVertexDataVB.SetBuffer();
			context.DrawArrays(Renderer::PRIM_LINE_STRIP_ADJACENCY, 0, m_VFXVertexData.size());
			//context.DrawArrays(Renderer::PRIM_LINE_STRIP, 0, m_VFXVertexData.size());
		}
		break;
	}
}

void CSpriteRenderer::Init()
{
	m_Effect= new CSpriteShader();
	m_Effect->Load();
	
	CMeshData meshData;
	CGeomCreator geomCreator;
	geomCreator.CreateQuad(meshData);

	m_PosVB.InputSlot(0);
	m_PosVB.SetData(meshData.Positions);
	m_Tex0VB.InputSlot(1);
	m_Tex0VB.SetData(meshData.UV0);

	m_IB.SetData(meshData.Indices);

	// InstanceData
	{
		CSpriteShader::INSTANCE_DATA inst_data[] = 
		{
			{ glm::vec4(-0.5, 0.5, 0, 0.1), glm::vec4(1, 0, 0, 1) },
			{ glm::vec4(-0.5, -0.5, 0, 0.1), glm::vec4(1, 1, 0, 1) },
			{ glm::vec4(0.5, 0.5, 0, 0.1), glm::vec4(0, 1, 0, 1) },
			{ glm::vec4(0.5, -0.5, 0, 0.1), glm::vec4(0, 1, 1, 1) }
		};

		copy(inst_data, inst_data + 4, back_inserter(m_InstanceData));
		m_InstanceVB.SetData(m_InstanceData);
		m_InstanceVB.InputSlot(2);
	}

	// Texture
	CImage8888 noiseTexture;
	{
		CImageF32 noiseTextureF32;
		noiseTextureF32.Resize(2,2);
		noiseTextureF32(0, 0) = glm::vec4(1,0,0,1);
		noiseTextureF32(1, 0) = glm::vec4(0,1,0,1);
		noiseTextureF32(0, 1) = glm::vec4(0,0,1,1);
		noiseTextureF32(1, 1) = glm::vec4(1,1,0,1);
		noiseTexture = noiseTextureF32.ToImage8888();
	}

	//m_TexDiffuse = new CTexture2DStatic();
	//m_TexDiffuse->SetData( Global::Renderer(), noiseTexture);

	// Ribbon VFX
	m_VFXRibbonEffect = new CVFXRibbonShader();
	m_VFXRibbonEffect->Load();

	m_VFXVertexDataVB.InputSlot(0);
	m_VFXVertexDataVB.BufferUsage(DYNAMIC_DRAW);
}

// eof /////////////////////////////////////////////


