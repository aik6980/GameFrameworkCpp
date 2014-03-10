//--------------------------------------------------
// File:    Scene.cpp
// Created: 31/03/2013 21:09:26
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "Scene.h" 

#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"

#include "Graphic/View/RenderView.h"
#include "Graphic/View/MainView.h"
#include "Graphic/Renderer/SpriteRenderer.h"
#include "Graphic/Renderer/RigidRenderer.h"

void CScene::Initialize()
{
	// create all renderer
	CSpriteRenderer* sprite_renderer = new CSpriteRenderer();
	m_RendererList.insert(make_pair(SPRITE_RENDERER, sprite_renderer));
	CRigidRenderer* rigid_renderer	 = new CRigidRenderer();
	m_RendererList.insert(make_pair(RIGID_RENDERER, rigid_renderer));

	// create all possible views
	CBaseRenderView* rw = new CMainView();
	rw->AddRenderer(*sprite_renderer);
	rw->AddRenderer(*rigid_renderer);
	m_RenderViews.push_back(rw);
}

void CScene::Render()
{
	CGLDevice& context = Global::Renderer();

	// PreRender
	for_each(m_RenderViews.begin(), m_RenderViews.end(),
		[&context](CBaseRenderView* obj)
		{
			obj->PreRender(context);
		});

	// Render a frame
	for_each(m_RenderViews.begin(), m_RenderViews.end(),
		[&context](CBaseRenderView* obj)
		{
			obj->Render(context);
		});

	// end of the frame
	Global::Renderer().SwapBuffers();

	// PostRender
	for_each(m_RenderViews.begin(), m_RenderViews.end(),
		[&context](CBaseRenderView* obj)
		{
			obj->PreRender(context);
		});
}

bool CScene::AddCameraToView( RenderViewID id, CBaseCamera& camera )
{
	CBaseRenderView* rv = GetRenderView(id);
	if(rv)
	{
		rv->AddCamara(camera);
		return true;
	}

	return false;
}

CBaseRenderView* CScene::GetRenderView( RenderViewID id )
{
	auto found_it = find_if(m_RenderViews.begin(), m_RenderViews.end(), 
		[&id](CBaseRenderView* obj) { return obj->GetRenderViewID() == id;});
	
	return (found_it!=m_RenderViews.end()) ? *found_it : nullptr;
}

// eof /////////////////////////////////////////////
