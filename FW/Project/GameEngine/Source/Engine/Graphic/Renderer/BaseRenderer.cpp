// local includes //////////////////////////////////
#include "stdafx.h" 
#include "BaseRenderer.h"

void CBaseRenderer::PreRender(CGLDevice& context, RenderViewID currView)
{
	for_each(m_GameObjectRenderList.begin(), m_GameObjectRenderList.end(),
		[&context, currView, this](weak_ptr<CGameObjectRenderInterface> obj)
		{
			if (auto sp = obj.lock())
			{
				sp->PreRender(context, currView, m_RendererID);
			}
		});
}

void CBaseRenderer::PostRender(CGLDevice& context, RenderViewID currView)
{

}
