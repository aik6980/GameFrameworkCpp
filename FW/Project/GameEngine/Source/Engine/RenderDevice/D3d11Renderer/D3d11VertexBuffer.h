#pragma once
#ifndef D3d11VertexBuffer_h__
#define D3d11VertexBuffer_h__

#include "Core/Core.h"
#include "RenderDevice/D3d11Renderer/D3d11Defines.h"

class CD3d11Device;

class CD3dBufferBase
{
public:
	CD3dBufferBase() 
		: m_Data(nullptr)
	{
		ZeroMemory(&m_DataDesc, sizeof(m_DataDesc));
	}

	void SetData(void* pData, uint32_t size);
protected:
	ID3D11Buffer*		m_Data;
	D3D11_BUFFER_DESC	m_DataDesc;
};

template<class T>
class CD3dVertexBufferStatic : CD3dBufferBase
{
public:
	CD3dVertexBufferStatic()
		: m_InputSlot(0),
		m_NumData(0)
	{
		m_DataDesc.Usage		= D3D11_USAGE_DEFAULT;
		m_DataDesc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	}

	void SetData(const vector<T>& data);
	void SetBuffer(CD3d11Device& context);

	uint32_t	GetInputSlot() const { return m_InputSlot; }
	void		SetInputSlot(uint32_t val) { m_InputSlot = val; }
	uint32_t	GetNumData() { return m_NumData; }
private:
	uint32_t m_InputSlot;
	uint32_t m_NumData;
};

template<class T>
class CD3dIndexBufferStatic : CD3dBufferBase
{
public:
	CD3dIndexBufferStatic() :
	  m_NumData(0)
	{
		m_DataDesc.Usage		= D3D11_USAGE_DEFAULT;
		m_DataDesc.BindFlags	= D3D11_BIND_INDEX_BUFFER;
	}

	DXGI_FORMAT	Mapping();
	void		SetData			(const vector<T>& data);
	void		Draw			(CD3d11Device& context);
	void		DrawInstancing	(CD3d11Device& context, uint32_t num_instances);
private:
	uint32_t m_NumData;
};

#endif // D3d11VertexBuffer_h__