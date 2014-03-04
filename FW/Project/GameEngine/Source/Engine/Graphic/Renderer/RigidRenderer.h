//--------------------------------------------------
// File:    RigidRenderer.h
// Created: 03/01/2014 12:19:33
//
// Description: $
//

//--------------------------------------------------

#ifndef _RIGIDRENDERER_H__2014_01_03_12_19_33
#define _RIGIDRENDERER_H__2014_01_03_12_19_33

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////


// type declarations (enum struct class) /////////
#include "BaseRenderer.h"
#include "Graphic/View/RenderView.h"
#include "Graphic/Shaders/RigidShader.h"
#include "Graphic/GeomCreator/GeomCreator.h"

#include "RenderDevice/RenderDevice.h"

class CMeshData;
class CTexture2DStatic;

class CRigidInstanceRenderData
{
public:

};

class CRigidRenderer : public CBaseRenderer
{
public:
	CRigidRenderer() : CBaseRenderer(RIGID_RENDERER) { Init(); };
	
	~CRigidRenderer()
	{
		Safe_Delete(m_Effect);
	}

	void Init();
	void Render(CGLDevice& context, RenderViewID currView);


private:
	CRigidShader*							m_Effect;

	CGLVertexBuffer<glm::vec3>				m_PosVB;
	CGLVertexBuffer<glm::vec2>				m_Tex0VB;
	CGLIndexBuffer<uint32_t>				m_IB;

	vector<CRigidShader::INSTANCE_DATA>				m_InstanceData;
	CGLVertexBuffer<CRigidShader::INSTANCE_DATA>	m_InstanceVB;

	// Indirect Draw Buffer
	CGLDrawIndirectBuffer<GLDrawElementsIndirectCommand>	m_DrawElementsCommand;

	// InstanceRenderData

	list<shared_ptr<CRigidInstanceRenderData>>		m_RigidInstances;
};


// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _RIGIDRENDERER_H__2014_01_03_12_19_33