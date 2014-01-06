//--------------------------------------------------
// File:    BaseShader.cpp
// Created: 16/03/2013 15:01:27
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "BaseShader.h" 

#include "Graphic/Camera/Camera.h"

CGLConstantBuffer<cbViewCommon> CBaseShader::m_CbViewCommon;
//CConstantBuffer<cbObjectCommon> CBaseShader::m_CbObjectCommon(1);

CBaseShader::CBaseShader()
{
	m_CbViewCommon.InputSlot(0);
}

void CBaseShader::SetViewCommonData( const CBaseCamera& camera )
{
	cbViewCommon cb0;

	cb0.ViewXf			= camera.View();
	cb0.ViewIXf			= camera.ViewInverse();
	cb0.ProjectionXf	= camera.Projection();
	cb0.ProjectionIXf	= glm::inverse(camera.Projection());

	m_CbViewCommon.SetData(cb0);
}

// eof /////////////////////////////////////////////
