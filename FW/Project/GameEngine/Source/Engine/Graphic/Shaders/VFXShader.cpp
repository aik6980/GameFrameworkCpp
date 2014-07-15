#include "stdafx.h"
#include "VFXShader.h"

#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Resource/ResourceManager.h" 

CVFXRibbonShader::CVFXRibbonShader()
: m_CurrTech(MAIN)
{
	m_Name = "VFXRibbonShader";
}

void CVFXRibbonShader::Load()
{
	{
		CResourceObject* vs_src = Global::ResourceManager().Get(GPUPROGRAM, "ParticleGS.vs");
		CResourceObject* gs_src = Global::ResourceManager().Get(GPUPROGRAM, "ParticleGS.gs");
		CResourceObject* ps_src = Global::ResourceManager().Get(GPUPROGRAM, "ParticleGS.ps");
		if (vs_src && gs_src && ps_src)
		{
			CGLRenderTechnique* t = new CGLRenderTechnique();
			t->SetName("Main");
			t->Load(*vs_src);
			t->Load(*gs_src);
			t->Load(*ps_src);

			// manually create an input desc
			CGLVertexInputLayout ia;
			ia.AddElement("POSITION", 0, Renderer::SHA_FMT_VEC4_FLOAT, 0);
			ia.AddElement("COLOR", 1, Renderer::SHA_FMT_VEC4_FLOAT, 0);

			CGLVertexShader* vs = t->GetShader<CGLVertexShader>(Renderer::SHA_VERTEX_SHADER);
			vs->SetInputLayoutDesc(ia);

			m_RenderTechniques.insert(make_pair(MAIN, t));
		}
	}
}

void CVFXRibbonShader::Apply()
{
	switch (m_CurrTech)
	{
	case MAIN:
		{
			m_RenderTechniques[MAIN]->Apply();
			m_CbViewCommon.SetBuffer();
		}
		break;
	}
}
