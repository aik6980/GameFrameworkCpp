// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11SamplerState.h" 

#include "Core/CoreCpp.h"
#include "RenderDevice/RenderDeviceCpp.h"

CSamplerStateBase::CSamplerStateBase(uint32_t id)
	: m_ID(id),
	m_Resource(nullptr)
{
	::ZeroMemory(&m_SamplerDesc, sizeof(m_SamplerDesc));

	m_SamplerDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	m_SamplerDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	m_SamplerDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;
}

void CSamplerStateBase::SetBuffer( CD3d11Device& context )
{
	if(!m_Resource)
	{
		context.GetDevice()->CreateSamplerState(&m_SamplerDesc, &m_Resource);
	}

	// Bind to the selected stages
	if(context.IsBindedPS())
	{
		context.GetDevImmediateContext()->PSSetSamplers(m_ID, 1, &m_Resource);
	}
}

CSamplerState_Point::CSamplerState_Point(uint32_t id)
	: CSamplerStateBase(id)
{
	m_SamplerDesc.Filter	= D3D11_FILTER_MIN_MAG_MIP_POINT;
}

CSamplerState_Linear::CSamplerState_Linear(uint32_t id)
	: CSamplerStateBase(id)
{
	m_SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
}

// eof /////////////////////////////////////////////


