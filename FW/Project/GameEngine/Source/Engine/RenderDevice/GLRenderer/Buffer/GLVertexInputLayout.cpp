// local includes //////////////////////////////////
#include "stdafx.h"
#include "GLVertexInputLayout.h" 


CGLVertexInputLayout::CGLVertexInputLayout()
	: m_OffsetInBytesToLastElem(0)
{
	glGenVertexArrays(1, &m_VAO);
}

void CGLVertexInputLayout::AddElement( string name, uint32_t layoutLocation, Renderer::DataFormat fmt, uint32_t inputSlot, uint32_t instance_data_step_rate /*= 0*/ )
{
	CGLVertexInputElem desc;
	desc.Name					= name;
	desc.LayoutLocation			= layoutLocation;
	desc.Fmt					= fmt;
	desc.InputSlot				= inputSlot;	// could be 0 .. 15, use in case of we are binding more than 1 VB (interleaving VB)
	desc.InstanceDataStepRate	= instance_data_step_rate; // The number of instances to draw before stepping one unit forward

	// handle a very first element
	if(m_IADesc.empty())
	{
		m_OffsetInBytesToLastElem = 0;
	}
	else
	{
		if(inputSlot == m_IADesc.back().InputSlot)
		{
			m_OffsetInBytesToLastElem += Renderer::SizeInBytes(m_IADesc.back().Fmt);
		}
		else
		{
			m_OffsetInBytesToLastElem = 0;
		}
	}

	desc.AlignedBytesOffset		= m_OffsetInBytesToLastElem;
	
	
	// add new inputElement to the list 
	m_IADesc.push_back(desc);
}

// eof /////////////////////////////////////////////



