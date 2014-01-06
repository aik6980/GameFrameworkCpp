#include "stdafx.h"
#include "RenderView.h" 

void CBaseRenderView::AddRenderer( CBaseRenderer& renderer )
{
	m_Renderers.push_back(&renderer);
}

void CBaseRenderView::AddCamara( CBaseCamera& camera )
{
	m_pCamera = &camera;
}