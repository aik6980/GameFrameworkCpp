#pragma once
#ifndef D3d11Texture_h__
#define D3d11Texture_h__

#include "RenderDevice/D3d11Renderer/D3dMcr.h"
#include "RenderDevice/RenderDevice.h"

class CD3d11Device;

class CTextureBase
{
public:
	CTextureBase()
		: m_SRV(nullptr)
	{

	}

	virtual ~CTextureBase()
	{
		SafeRelease(m_SRV);
	}

	ID3D11ShaderResourceView*			GetSRV(CD3d11Device& context);
protected:
	virtual ID3D11Resource*				GetResource()=0;
	ID3D11ShaderResourceView*			m_SRV;
};

#endif // D3d11Texture_h__