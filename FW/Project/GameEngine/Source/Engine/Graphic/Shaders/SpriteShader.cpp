//--------------------------------------------------
// File:    SpriteShader.cpp
// Created: 31/01/2013 09:31:15
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "SpriteShader.h"
#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Resource/ResourceManager.h" 

CGLConstantBuffer<CSpriteShader::CB02>		CSpriteShader::m_CB02;

//CTextureShaderResource					CSpriteShader::m_TexDiffuse(0);
//CSamplerState_Point						CSpriteShader::m_SamDiffuse(0);

CSpriteShader::CSpriteShader()
	: m_CurrTech(MAIN)
{
	m_Name = "SpriteShader";
	m_CB02.InputSlot(2);
}

void CSpriteShader::Load()
{
	/*{
		CResourceObject* resObj = Global::ResourceManager().Get(GPUPROGRAM, m_Name);
		if(resObj)
		{
			CGLRenderTechnique* t = new CGLRenderTechnique();
			t->SetName("Main");
			t->Load(Renderer::SHA_VERTEX_SHADER, resObj->m_Path);
			t->Load(Renderer::SHA_PIXEL_SHADER, resObj->m_Path);

			m_RenderTechniques.insert(make_pair(MAIN, t));
		}
	}*/

	{
		CResourceObject* vs_src = Global::ResourceManager().Get(GPUPROGRAM, "SpriteShader.vs");
		CResourceObject* ps_src = Global::ResourceManager().Get(GPUPROGRAM, "SpriteShader.ps");
		if(vs_src && ps_src)
		{
			CGLRenderTechnique* t = new CGLRenderTechnique();
			t->SetName("MainInstancing");
			t->Load(*vs_src);
			t->Load(*ps_src);

			// manually create an input desc
			CGLVertexInputLayout ia;
			ia.AddElement("POSITION", 0,		Renderer::SHA_FMT_VEC3_FLOAT, 0);
			ia.AddElement("TEXCOORD0", 1,		Renderer::SHA_FMT_VEC2_FLOAT, 1);
			ia.AddElement("INST_POSITION", 2,	Renderer::SHA_FMT_VEC4_FLOAT, 2, 1);
			ia.AddElement("INST_COLOR", 3,		Renderer::SHA_FMT_VEC4_FLOAT, 2, 1);
			
			CGLVertexShader* vs = t->GetShader<CGLVertexShader>(Renderer::SHA_VERTEX_SHADER);
			vs->SetInputLayoutDesc(ia);

			m_RenderTechniques.insert(make_pair(MAIN_INSTANCING, t));
		}
	}
}

void CSpriteShader::Apply()
{
	switch(m_CurrTech)
	{
	case MAIN:
		{
			m_RenderTechniques[MAIN]->Apply();

			//m_CbViewCommon.SetBuffer(context);
			//m_CbObjectCommon.SetBuffer(context);
			//m_CB02.SetBuffer(context);

			//m_TexDiffuse.SetBuffer(context);
			//m_SamDiffuse.SetBuffer(context);
		}
		break;
	case MAIN_INSTANCING:
		{
			m_RenderTechniques[MAIN_INSTANCING]->Apply();

			//m_CbViewCommon.SetBuffer(context);
			//m_CbObjectCommon.SetBuffer(context);
			m_CB02.SetBuffer();

			//m_TexDiffuse.SetBuffer(context);
			//m_SamDiffuse.SetBuffer(context);
		}
		break;
	}
}

// eof /////////////////////////////////////////////

