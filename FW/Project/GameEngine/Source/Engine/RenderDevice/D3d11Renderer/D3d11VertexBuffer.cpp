//--------------------------------------------------
// File:    D3d11VertexBuffer.cpp
// Created: 12/04/2013 03:00:23
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "D3d11VertexBuffer.h" 

void CD3dBufferBase::SetData( void* pData, uint32_t size )
{
	if(!m_Data)
	{
		m_DataDesc.ByteWidth = size;
		Debug::Assert(false, "incomplete Function");
		// Comment out because of OpenGL 
		//Global::Renderer().CreateBuffer(m_Data, m_DataDesc, pData);
	}
}


template<class T>
void CD3dVertexBufferStatic<T>::SetData( const vector<T>& data )
{
	if(!m_Data)
	{
		CD3dBufferBase::SetData((void*)&data[0], data.size() * sizeof(T));
		m_NumData = data.size();
	}
	else
	{
		// update buffer using copy sub-resource
	}
}

template<class T>
void CD3dVertexBufferStatic<T>::SetBuffer( CD3d11Device& context )
{
	uint32_t strides[1] = {sizeof(T)};
	uint32_t offsets[1] = {0};
	context.GetDevImmediateContext()->IASetVertexBuffers(m_InputSlot, 1, &m_Data, strides, offsets);
}

template<class T>
DXGI_FORMAT CD3dIndexBufferStatic<T>::Mapping()
{
	switch( sizeof(T) )
	{
	case 2: return DXGI_FORMAT_R16_UINT;
	case 4: return DXGI_FORMAT_R32_UINT;
	default:
		Debug::Assert(false, "IndexFormat conversion failed\n");
	}

	return DXGI_FORMAT_R32_TYPELESS;
}

template<class T>
void CD3dIndexBufferStatic<T>::SetData( const vector<T>& data )
{
	if(!m_Data)
	{
		CD3dBufferBase::SetData((void*)&data[0], data.size() * sizeof(T));
		m_NumData = data.size();
	}
	else
	{
		// update buffer using copy sub-resource
	}
}

template<class T>
void CD3dIndexBufferStatic<T>::Draw( CD3d11Device& context )
{
	context.GetDevImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context.GetDevImmediateContext()->IASetIndexBuffer(m_Data, Mapping(), 0);
	context.GetDevImmediateContext()->DrawIndexed(m_NumData, 0, 0);
}

template<class T>
void CD3dIndexBufferStatic<T>::DrawInstancing( CD3d11Device& context, uint32_t num_instances)
{
	context.GetDevImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context.GetDevImmediateContext()->IASetIndexBuffer(m_Data, Mapping(), 0);
	context.GetDevImmediateContext()->DrawIndexedInstanced(m_NumData, num_instances, 0, 0, 0);
}

// eof /////////////////////////////////////////////


