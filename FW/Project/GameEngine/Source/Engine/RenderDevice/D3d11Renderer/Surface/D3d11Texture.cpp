// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11Texture.h"

#include "RenderDevice/D3d11Renderer/D3d11Device.h"

ID3D11ShaderResourceView* CTextureBase::GetSRV( CD3d11Device& context )
{
	if(!m_SRV)
	{
		context.GetDevice()->CreateShaderResourceView(GetResource(), nullptr, &m_SRV);
	}

	return m_SRV;
}

// eof /////////////////////////////////////////////
