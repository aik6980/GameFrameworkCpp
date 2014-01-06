#include "stdafx.h"
#include "D3d11Texture2D.h"

#include "Core/CoreCpp.h"
#include "RenderDevice/D3d11Renderer/D3d11Device.h"
#include "RenderDevice/SoftwareRenderer/Image/Image.h"

CTexture2DBase::CTexture2DBase()
	: m_Resource(nullptr)
{
	::ZeroMemory(&m_ResourceDesc, sizeof(m_ResourceDesc));
	m_ResourceDesc.Width = 0;
	m_ResourceDesc.Height = 0;
	m_ResourceDesc.ArraySize = 1;
	m_ResourceDesc.SampleDesc.Count = 1;
	m_ResourceDesc.SampleDesc.Quality = 0;
	m_ResourceDesc.Format	= DXGI_FORMAT_UNKNOWN;
	m_ResourceDesc.Usage	= D3D11_USAGE_DEFAULT;
	m_ResourceDesc.MipLevels = 1;
	m_ResourceDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
}

void CTexture2DBase::SetData( CD3d11Device& context, CImageBase& imgData )
{
	if(!m_Resource)
	{
		m_ResourceDesc.Width	= imgData.GetWidth();
		m_ResourceDesc.Height	= imgData.GetHeight();
		m_ResourceDesc.Format	= ToDXGIFmt(imgData.GetImgFmt());
		m_ResourceDesc.Usage	= D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA data_info;
		ZeroMemory(&data_info, sizeof(data_info));
		data_info.pSysMem		= imgData.GetRawData();
		data_info.SysMemPitch	= imgData.GetMemPitch();

		HRESULT hr = context.GetDevice()->CreateTexture2D(&m_ResourceDesc, &data_info, &m_Resource);
		if( FAILED( hr ) )
		{
			Debug::Print(L"Failed to create a texture2d.");
		}
	}
}

DXGI_FORMAT CTexture2DBase::ToDXGIFmt( Renderer::ImageFormatType img_fmt )
{
	switch(img_fmt)
	{
	case Renderer::IMGFMT_R8G8B8A8_UNORM			:	return DXGI_FORMAT_B8G8R8A8_UNORM;
	case Renderer::IMGFMT_R32G32B32A32_FLOAT		:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
	default:
		Debug::Assert(false, "ToDXGIFmt() Failed");
		return DXGI_FORMAT_UNKNOWN;
	}
}
