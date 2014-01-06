//--------------------------------------------------
// File:    D3d11RenderState.cpp
// Created: 28/02/2013 08:59:38
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11RenderState.h" 

#include "RenderDevice/D3d11Renderer/D3d11Device.h"

CDefaultDepthStencil::CDefaultDepthStencil() : 
	m_StateHandle(nullptr),
	m_StencilRef(0)
{
	D3D11_DEPTH_STENCIL_DESC desc;

	desc.DepthEnable		= TRUE;
	desc.DepthWriteMask		= D3D11_DEPTH_WRITE_MASK_ALL; // depth write, ON
	desc.DepthFunc			= D3D11_COMPARISON_LESS_EQUAL;

	desc.StencilEnable		= FALSE;
	desc.StencilReadMask	= D3D11_DEFAULT_STENCIL_READ_MASK;	// 0xff, always pass
	desc.StencilWriteMask	= D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff, always pass

	D3D11_DEPTH_STENCILOP_DESC opdesc = 
	{  
		D3D11_STENCIL_OP_KEEP, 
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_KEEP,
		D3D11_COMPARISON_ALWAYS
	};
	desc.FrontFace	= opdesc; 
	desc.BackFace	= opdesc;

	m_Desc = desc;
}

void CDefaultDepthStencil::SetRenderState( CD3d11Device & context )
{
	if(!m_StateHandle)
	{
		context.GetDevice()->CreateDepthStencilState(&m_Desc, &m_StateHandle);
	}

	context.GetDevImmediateContext()->OMSetDepthStencilState(m_StateHandle, m_StencilRef);
}

CDefaultBlend::CDefaultBlend()
{
	D3D11_BLEND_DESC desc;

	desc.AlphaToCoverageEnable = FALSE;
	desc.IndependentBlendEnable = FALSE; // all RTs is blended using similar setup

#define MAINRT 0 
	desc.RenderTarget[MAINRT].BlendEnable = FALSE;
	desc.RenderTarget[MAINRT].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	desc.RenderTarget[MAINRT].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[MAINRT].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[MAINRT].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[MAINRT].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[MAINRT].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[MAINRT].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
#undef MAINRT

	m_Desc = desc;

	std::fill(m_BlendFactor, m_BlendFactor + NUM_ELEM(m_BlendFactor), 1.0f);
	m_SampleMask = UINT_MAX;
}

void CDefaultBlend::SetRenderState( CD3d11Device & context )
{
	if(!m_StateHandle)
	{
		context.GetDevice()->CreateBlendState(&m_Desc, &m_StateHandle);
	}

	context.GetDevImmediateContext()->OMSetBlendState(m_StateHandle, m_BlendFactor, m_SampleMask);
}

CDefaultRasterizer::CDefaultRasterizer()
{
	D3D11_RASTERIZER_DESC desc;

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = FALSE; // following the left-handed system
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f; // maximum depth bias, 0.0f means no clamp 
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthClipEnable = TRUE;
	desc.ScissorEnable = FALSE;
	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	m_Desc = desc; 
}

void CDefaultRasterizer::SetRenderState( CD3d11Device & context )
{
	if(!m_StateHandle)
	{
		context.GetDevice()->CreateRasterizerState(&m_Desc, &m_StateHandle);
	}

	context.GetDevImmediateContext()->RSSetState(m_StateHandle);
}

// eof /////////////////////////////////////////////
