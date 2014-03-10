#pragma once
#ifndef Scene_h__
#define Scene_h__

#include "Graphic/View/RenderView.h"
#include "Graphic/Renderer/BaseRenderer.h"

class CBaseRenderView;
class CBaseRenderer;
class CSpriteRenderer;
class CRigidRenderer;

class CBaseCamera;

class CScene
{
public:
	void	Initialize();
	void	Render();

	bool	AddCameraToView(RenderViewID id, CBaseCamera& camera);

	template<class T>
	T*		GetRenderer(RendererID id)
	{
		auto it = m_RendererList.find(id);
		if (it != m_RendererList.end())
			return static_cast<T*>(it->second);
		else
			return nullptr;
	}
private:
	CBaseRenderView*	GetRenderView(RenderViewID id);

	vector<CBaseRenderView*>					m_RenderViews;
	// Renderer
	unordered_map<RendererID, CBaseRenderer*>	m_RendererList;
};

#endif // Scene_h__