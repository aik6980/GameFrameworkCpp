#include "stdafx.h"
#include "D3dMcr.h"

uint32_t SizeInBytes(DXGI_FORMAT fmt)
{
	switch(fmt)
	{
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		return sizeof(float) * 4;
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_TYPELESS:
		return sizeof(float) * 2;
	default:
		Debug::Assert(false, "Unsupported DXGI_FORMAT Type");
		return 0;
	}
}
