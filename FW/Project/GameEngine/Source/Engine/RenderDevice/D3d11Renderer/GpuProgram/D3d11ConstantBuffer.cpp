//--------------------------------------------------
// File:    D3d11ConstantBuffer.cpp
// Created: 03/02/2013 23:50:02
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11ConstantBuffer.h"

#include "RenderDevice/D3d11Renderer/D3dMcr.h"
#include "RenderDevice/D3d11Renderer/D3d11Device.h"

void CConstantBufferBase::BindBufferToShader( CD3d11Device& context )
{
	if(context.IsBindedVS())
	{
		context.GetDevImmediateContext()->VSSetConstantBuffers(m_ID, 1, &m_D3dBuffer);
	}

	if(context.IsBindedPS())
	{
		context.GetDevImmediateContext()->PSSetConstantBuffers(m_ID, 1, &m_D3dBuffer);
	}
}

template<class T>
void CConstantBuffer<T>::SetBuffer( CD3d11Device& context )
{
	// ask for a buffer if we haven't created one yet
	if(!m_D3dBuffer)
	{
		context.CreateConstantBuffer(m_D3dBuffer, sizeof(m_Data), &m_Data);
	}

	// Update resource
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	context.GetDevImmediateContext()->Map(m_D3dBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
	memcpy(mappedSubResource.pData, &m_Data, sizeof(m_Data));
	context.GetDevImmediateContext()->Unmap(m_D3dBuffer, 0);

	// Bind to the render pipeline
	BindBufferToShader(context);
}

void CTextureShaderResource::SetResource( ID3D11ShaderResourceView* srv )
{
	// if this is the same resource, do nothing
	if(m_Resource == srv) { return; }

	// release the current resource, point to the new one and add one ref to it
	SafeRelease(m_Resource);
	if(srv)
	{
		m_Resource = srv;
		m_Resource->AddRef();
	}
}

void CTextureShaderResource::SetBuffer( CD3d11Device& context )
{
	if(context.IsBindedPS())
	{
		context.GetDevImmediateContext()->PSSetShaderResources(m_Id, 1, &m_Resource);
	}
}

// eof /////////////////////////////////////////////

