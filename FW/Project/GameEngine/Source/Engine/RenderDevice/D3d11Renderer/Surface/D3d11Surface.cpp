#include "stdafx.h"
#include "D3d11Surface.h"

#include "RenderDevice/D3d11Renderer/D3d11Device.h"

// void D3d11RenderSurface::CreateSurface2D( ID3D11Device* _dev, 
// 	const D3D11_TEXTURE2D_DESC& _desc, SurfaceType _t )
// {
// 	ID3D11Texture2D** buffer = NULL;
// 	ID3D11ShaderResourceView** srv = NULL;
// 	switch(_t)
// 	{
// 	case RT_COLOR:
// 		buffer = &m_ColorBuffer.m_Resource;
// 		srv = &m_ColorBuffer.m_SRV;
// 		break;
// 	case RT_DEPTH:
// 		buffer = &m_DepthBuffer.m_Resource;
// 		srv = &m_DepthBuffer.m_SRV;
// 		break;
// 	}
// 	_dev->CreateTexture2D (&_desc, NULL, buffer);
// 	_dev->CreateShaderResourceView(*buffer, NULL, srv);
// 
// 	switch(_t)
// 	{
// 	case RT_COLOR:
// 		_dev->CreateRenderTargetView( m_ColorBuffer.m_Resource, NULL, &m_ColorBuffer.m_RTV);
// 		break;
// 	case RT_DEPTH:
// 		_dev->CreateDepthStencilView( m_ColorBuffer.m_Resource, NULL, &m_DepthBuffer.m_RTV);
// 		break;
// 	}
// }

void CD3d11ColorRT::GetResource(CD3d11Device& context)
{
	if(!m_Resource)
	{
		context.GetDevice()->CreateTexture2D (&m_Desc, NULL, &m_Resource);
	}
}

void CD3d11ColorRT::SetRenderTarget( CD3d11Device& context )
{
	if(!m_RTV)
	{
		context.GetDevice()->CreateRenderTargetView( m_Resource, NULL, &m_RTV);
	}
}
