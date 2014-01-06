#pragma once
#ifndef Scene_h__
#define Scene_h__

#include "Graphic/View/RenderView.h"

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
private:
	CBaseRenderView*	GetRenderView(RenderViewID id);

	vector<CBaseRenderView*>	m_RenderViews;
	// Renderer
	CSpriteRenderer*			m_SpriteRenderer;
	CRigidRenderer*				m_RigidRenderer;
};

#endif // Scene_h__