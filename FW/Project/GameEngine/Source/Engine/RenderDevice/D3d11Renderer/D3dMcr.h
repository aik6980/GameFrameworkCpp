#pragma once
#ifndef DxMcr_h__
#define DxMcr_h__

#include "Core/Core.h"
#include "D3d11Defines.h"

template <typename T>
void SafeRelease(T x)
{
	if(x != NULL)
	{
		x->Release();
		x = NULL;
	}
}

template <typename T>
inline HRESULT HR_Return(T x)
{
	HRESULT hr = (x);
	if(FAILED(hr))
	{
		std::string enumStr = DXGetErrorStringA(hr);
		std::string descStr = DXGetErrorDescriptionA(hr);
		Debug::Print((boost::format("%1% : %2% at %3% %4%") % enumStr % descStr % __FILE__ % __LINE__).str());
		return hr;
	}

	return S_OK;
}

uint32_t SizeInBytes(DXGI_FORMAT fmt);

#endif // DxMcr_h__