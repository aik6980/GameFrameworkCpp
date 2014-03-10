#pragma once
#ifndef BaseRenderer_h__
#define BaseRenderer_h__

#include "Graphic/View/RenderView.h"

enum RendererID
{
	SPRITE_RENDERER,
	RIGID_RENDERER,
};

class CGameObjectRenderInterface
{
public:
	virtual void PreRender(CGLDevice& context, RenderViewID currView, RendererID currRenderer) = 0;
};

class CBaseRenderer
{
public:
	CBaseRenderer(const RendererID id) : m_RendererID(id) {};

	virtual void PreRender(CGLDevice& context, RenderViewID currView);
	virtual void Render( CGLDevice& context, RenderViewID currView )=0;
	virtual void PostRender(CGLDevice& context, RenderViewID currView);

	void	RegisterGameObject(weak_ptr<CGameObjectRenderInterface> obj) { m_GameObjectRenderList.push_back(obj); }
private:
	const RendererID	m_RendererID;

	// CGameObjectRenderInterface List
	vector<weak_ptr<CGameObjectRenderInterface>> m_GameObjectRenderList;
};

#endif // BaseRenderer_h__