//--------------------------------------------------
// File:    MainView.cpp
// Created: 31/03/2013 14:56:40
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "MainView.h"

#include "Global.h"
#include "RenderDevice/RenderDeviceCpp.h"
#include "Graphic/Renderer/BaseRenderer.h"

#include "Graphic/Shaders/BaseShader.h"

void CMainView::Render(CGLDevice& context)
{
	// 1. setup RT/Depth
	glm::vec4 clearCol( 0.0f, 0.0f, 0.0f, 0.0f );
	Global::Renderer().Clear( clearCol, 1.0f );

	// 2. setup camera for this view
	CBaseShader::SetViewCommonData(*m_pCamera);

	// 3. draw all registered renderer
	for_each(m_Renderers.begin(), m_Renderers.end(), 
		[&context, this](CBaseRenderer* obj)
		{
			obj->Render(context, m_ViewID);
		});
}

// eof /////////////////////////////////////////////

