#pragma once

#ifndef D3d11RenderState_h__
#define D3d11RenderState_h__

#include "RenderDevice/D3d11Renderer/D3d11Defines.h"

class CD3d11Device;

class CBaseRenderState
{
public:
	virtual void SetRenderState(CD3d11Device & context)=0;
};

class CDefaultDepthStencil : public CBaseRenderState
{
public:
	CDefaultDepthStencil();

	virtual void SetRenderState(CD3d11Device & context);
private:
	D3D11_DEPTH_STENCIL_DESC	m_Desc;
	UINT						m_StencilRef;

	ID3D11DepthStencilState*	m_StateHandle;
};

class CDefaultBlend : public CBaseRenderState
{
	CDefaultBlend();

	virtual void SetRenderState(CD3d11Device & context);
private:
	D3D11_BLEND_DESC	m_Desc;
	float				m_BlendFactor[4];
	uint32_t			m_SampleMask;

	ID3D11BlendState*	m_StateHandle;
};

class CDefaultRasterizer : public CBaseRenderState
{
	CDefaultRasterizer();

	virtual void SetRenderState(CD3d11Device & context);
private:
	D3D11_RASTERIZER_DESC m_Desc;

	ID3D11RasterizerState* m_StateHandle;
};

#endif // D3d11RenderState_h__