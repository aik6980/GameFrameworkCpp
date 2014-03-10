#include "stdafx.h"
#include "RenderView.h" 

#include "Graphic/Renderer/BaseRenderer.h"

void CBaseRenderView::PreRender(CGLDevice& context)
{
	for_each(m_Renderers.begin(), m_Renderers.end(),
		[&context, this](CBaseRenderer* obj)
	{
		obj->PreRender(context, m_ViewID);
	});
}

void CBaseRenderView::PostRender(CGLDevice& context)
{
	for_each(m_Renderers.begin(), m_Renderers.end(),
		[&context, this](CBaseRenderer* obj)
	{
		obj->PostRender(context, m_ViewID);
	});
}

void CBaseRenderView::AddRenderer( CBaseRenderer& renderer )
{
	m_Renderers.push_back(&renderer);
}

void CBaseRenderView::AddCamara( CBaseCamera& camera )
{
	m_pCamera = &camera;
}
