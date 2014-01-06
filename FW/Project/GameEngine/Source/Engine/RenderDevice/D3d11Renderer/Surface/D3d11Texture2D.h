#pragma once
#ifndef D3d11Texture2D_h__
#define D3d11Texture2D_h__

#include "Core/Core.h"
#include "D3d11Texture.h"

class CImageBase;
class CImage;

class CTexture2DBase : public CTextureBase
{
public:
	CTexture2DBase();

	virtual ~CTexture2DBase()
	{
		SafeRelease(m_Resource);
	}

	void		SetData(CD3d11Device& context, CImageBase& imgData);
protected:
	virtual ID3D11Resource* GetResource() { return m_Resource; }

	DXGI_FORMAT				ToDXGIFmt(Renderer::ImageFormatType img_fmt);


	D3D11_TEXTURE2D_DESC	m_ResourceDesc;
	ID3D11Texture2D*		m_Resource;
};

class CTexture2DStatic : public CTexture2DBase
{
public:
private:
};

#endif // D3d11Texture2D_h__