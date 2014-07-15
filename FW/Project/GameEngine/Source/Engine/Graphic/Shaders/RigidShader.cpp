// local includes //////////////////////////////////
#include "stdafx.h"
#include "RigidShader.h"
#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Resource/ResourceManager.h" 

CRigidShader::CRigidShader()
	: m_CurrTech(MAIN_INSTANCING)
{
	m_Name = "RigidShader";
}

void CRigidShader::Load()
{
	{
		CResourceObject* vs_src = Global::ResourceManager().Get(GPUPROGRAM, "RigidShader.vs");
		CResourceObject* ps_src = Global::ResourceManager().Get(GPUPROGRAM, "RigidShader.ps");
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
			ia.AddElement("INST_ROTATION", 3,	Renderer::SHA_FMT_VEC4_FLOAT, 2, 1);
			
			CGLVertexShader* vs = t->GetShader<CGLVertexShader>(Renderer::SHA_VERTEX_SHADER);
			vs->SetInputLayoutDesc(ia);

			m_RenderTechniques.insert(make_pair(MAIN_INSTANCING, t));
		}
	}
}

void CRigidShader::Apply()
{
	switch(m_CurrTech)
	{
	case MAIN_INSTANCING:
		{
			m_RenderTechniques[MAIN_INSTANCING]->Apply();
			m_CbViewCommon.SetBuffer();

			//m_CbObjectCommon.SetBuffer(context);

			//m_TexDiffuse.SetBuffer(context);
			//m_SamDiffuse.SetBuffer(context);
		}
		break;
	}
}


