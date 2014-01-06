#pragma once
#ifndef D3d11Surface_h__
#define D3d11Surface_h__

#include "Core/Core.h"

class CD3d11Device;

class CD3d11RenderTarget
{
public:
	CD3d11RenderTarget();
	~CD3d11RenderTarget();

	// create and destroy
	void CreateSurface2D(ID3D11Device* _dev, const D3D11_TEXTURE2D_DESC& _desc);
protected:
	D3D11_TEXTURE2D_DESC	m_Desc;
private:
};

class CD3d11ColorRT : public CD3d11RenderTarget
{
public:
	CD3d11ColorRT() : m_Resource(nullptr),
		m_RTV(nullptr),
		m_SRV(nullptr)
	{}

	void GetResource(CD3d11Device& context);
	void SetRenderTarget(CD3d11Device& context);
private:
	ID3D11Texture2D* m_Resource;
	ID3D11ShaderResourceView* m_SRV;
	ID3D11RenderTargetView* m_RTV;
};

class CD3d11DepthRT : public CD3d11RenderTarget
{
public:
	CD3d11DepthRT() : m_Resource(nullptr),
		m_RTV(nullptr),
		m_SRV(nullptr)
	{}
private:
	ID3D11Texture2D* m_Resource;
	ID3D11ShaderResourceView* m_SRV;
	ID3D11DepthStencilView* m_RTV;
};

#endif // D3d11Surface_h__