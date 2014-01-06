#pragma once
#ifndef D3d11SamplerState_h__
#define D3d11SamplerState_h__

#include "RenderDevice/RenderDevice.h"
#include "RenderDevice/D3d11Renderer/D3dMcr.h"

class CD3d11Device;

class CSamplerStateBase
{
public:
	CSamplerStateBase(uint32_t id);
	~CSamplerStateBase()  { SafeRelease(m_Resource); }

	void		SetBuffer		(CD3d11Device& context);
protected:
	uint32_t			m_ID;
	D3D11_SAMPLER_DESC	m_SamplerDesc;
	ID3D11SamplerState* m_Resource;
};

class CSamplerState_Point : public CSamplerStateBase
{
public:
	CSamplerState_Point(uint32_t id);
};

class CSamplerState_Linear : public CSamplerStateBase
{
public:
	CSamplerState_Linear(uint32_t id);
};

#endif // D3d11SamplerState_h__