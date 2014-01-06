#include "stdafx.h"
#include "D3d11GpuProgParam.h"
#include "RenderDevice/D3d11Renderer/D3dMcr.h"

D3D11_INPUT_ELEMENT_DESC CGpuProgInputElem::ToD3d11Desc()
{
	D3D11_INPUT_ELEMENT_DESC desc;
	desc.SemanticName	= Name.c_str();
	desc.SemanticIndex	= Index;
	desc.Format			= Fmt;
	desc.InputSlot		= InputSlot;	// could be 0 .. 15, use in case of we are binding more than 1 VB (interleaving VB)
	desc.InputSlotClass			= UseAsInstanceData ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate	= InstanceDataStepRate; // The number of instances to draw before stepping one unit forward
	desc.AlignedByteOffset		= AlignedBytesOffset;
	return desc; 
}

CInputLayoutDesc::CInputLayoutDesc()
	: m_OffsetInBytesToLastElem_VertexData(0),
	m_OffsetInBytesToLastElem_Instance(0)
{

}

void CInputLayoutDesc::AddElement(string name, uint32_t index, DXGI_FORMAT fmt, uint32_t input_slot, bool use_as_instance_data, uint32_t instance_data_step_rate)
{
	CGpuProgInputElem desc;
	desc.Name	= name;
	desc.Index	= index;
	desc.Fmt	= fmt;
	desc.InputSlot			= input_slot;	// could be 0 .. 15, use in case of we are binding more than 1 VB (interleaving VB)
	desc.UseAsInstanceData	= use_as_instance_data;
	desc.InstanceDataStepRate = instance_data_step_rate; // The number of instances to draw before stepping one unit forward
	desc.AlignedBytesOffset = use_as_instance_data ? m_OffsetInBytesToLastElem_Instance : m_OffsetInBytesToLastElem_VertexData; // this have to be set regarding to the Input structure

	// increase the offset
	if(use_as_instance_data)
	{
		m_IADesc_Instance.push_back(desc);	
		m_OffsetInBytesToLastElem_Instance += SizeInBytes(fmt);
	}
	else
	{
		m_IADesc.push_back(desc);
		m_OffsetInBytesToLastElem_VertexData += SizeInBytes(fmt);
	}
}

void CInputLayoutDesc::Clear()
{
	m_OffsetInBytesToLastElem_VertexData = 0;
	m_IADesc.clear();
	
	m_OffsetInBytesToLastElem_Instance = 0;
	m_IADesc_Instance.clear();
}

vector<D3D11_INPUT_ELEMENT_DESC> CInputLayoutDesc::GetD3D11InputLayoutDesc()
{
	vector<D3D11_INPUT_ELEMENT_DESC> result;
	for_each(m_IADesc.begin(), m_IADesc.end(), 
		[&result](CGpuProgInputElem& obj)
		{ 
			D3D11_INPUT_ELEMENT_DESC elem = obj.ToD3d11Desc();
			result.push_back(elem);
		});

	for_each(m_IADesc_Instance.begin(), m_IADesc_Instance.end(), 
		[&result](CGpuProgInputElem& obj)
		{ 
			D3D11_INPUT_ELEMENT_DESC elem = obj.ToD3d11Desc();
			result.push_back(elem);
		});

	return result;
}




