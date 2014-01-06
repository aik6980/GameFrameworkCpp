#pragma once
#ifndef D3d11GpuProgParam_h__
#define D3d11GpuProgParam_h__

#include "Core/Core.h"

struct CGpuProgInputElem
{
	string		Name;
	uint32_t	Index;
	DXGI_FORMAT	Fmt;
	uint32_t	InputSlot;
	bool		UseAsInstanceData;
	uint32_t	InstanceDataStepRate;
	uint32_t	AlignedBytesOffset;

	D3D11_INPUT_ELEMENT_DESC ToD3d11Desc();
};

class CInputLayoutDesc
{
public:
	CInputLayoutDesc();

	void Clear();
	uint32_t NumElems() { return m_IADesc.size(); }
	void AddElement(string name, uint32_t index, DXGI_FORMAT fmt, uint32_t input_slot, bool use_as_instance_data = false, uint32_t instance_data_step_rate = 0);

	vector<D3D11_INPUT_ELEMENT_DESC> GetD3D11InputLayoutDesc();
private:
	vector<CGpuProgInputElem> m_IADesc;
	vector<CGpuProgInputElem> m_IADesc_Instance;
	
	uint32_t m_OffsetInBytesToLastElem_VertexData;
	uint32_t m_OffsetInBytesToLastElem_Instance;
};

#endif // D3d11GpuProgParam_h__