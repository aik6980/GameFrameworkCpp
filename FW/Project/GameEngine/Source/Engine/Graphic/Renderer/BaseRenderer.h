#pragma once
#ifndef BaseRenderer_h__
#define BaseRenderer_h__

#include "Graphic/View/RenderView.h"

enum RendererID
{
	SPRITE_RENDERER,
	RIGID_RENDERER,
};

class CBaseRenderer
{
public:
	CBaseRenderer(const RendererID id) : m_RendererID(id) {};

	virtual void Render( CGLDevice& context, RenderViewID currView )=0;
private:
	const RendererID	m_RendererID;
};

#endif // BaseRenderer_h__