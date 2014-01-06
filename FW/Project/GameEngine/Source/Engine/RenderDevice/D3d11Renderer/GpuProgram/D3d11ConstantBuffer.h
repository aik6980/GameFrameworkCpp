#pragma once
#ifndef D3d11ConstantBuffer_h__
#define D3d11ConstantBuffer_h__

#include "RenderDevice/D3d11Renderer/D3dMcr.h"

class CD3d11Device;

class CConstantBufferBase
{
public:
	CConstantBufferBase(uint32_t id)
		: m_ID(id),
		m_D3dBuffer(nullptr)
	{ }

	virtual ~CConstantBufferBase()
	{
		SafeRelease(m_D3dBuffer);
	}

	virtual void		SetBuffer(CD3d11Device& context)=0;

protected:
	void				BindBufferToShader(CD3d11Device& context);

	uint32_t			m_ID;
	ID3D11Buffer*		m_D3dBuffer;
};

template<class T>
class CConstantBuffer : CConstantBufferBase
{
public:
	CConstantBuffer(uint32_t id) 
		: CConstantBufferBase(id)
	{ }

	virtual void		SetBuffer(CD3d11Device& context);

	T			m_Data;
};

class CTextureShaderResource
{
public:
	CTextureShaderResource(uint32_t id)
		: m_Id(id),
		m_Resource(nullptr)
	{ }

	~CTextureShaderResource()
	{
		SafeRelease(m_Resource);
	}

	void		SetResource(ID3D11ShaderResourceView* srv);
	void		SetBuffer(CD3d11Device& context);
private:
	uint32_t					m_Id;
	ID3D11ShaderResourceView*	m_Resource;
};

#endif // D3d11ConstantBuffer_h__