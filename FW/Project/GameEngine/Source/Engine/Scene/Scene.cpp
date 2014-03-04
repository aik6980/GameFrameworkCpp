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
	m_SpriteRenderer = new CSpriteRenderer();
	m_RigidRenderer	 = new CRigidRenderer();

	// create all possible views
	CBaseRenderView* rw = new CMainView();
	rw->AddRenderer(*m_SpriteRenderer);
	rw->AddRenderer(*m_RigidRenderer);
	m_RenderViews.push_back(rw);
}

void CScene::Render()
{
	CGLDevice& context = Global::Renderer();

	for_each(m_RenderViews.begin(), m_RenderViews.end(),
		[&context](CBaseRenderView* obj)
		{
			obj->Render(context);
		});

	// end of the frame
	Global::Renderer().SwapBuffers();
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
