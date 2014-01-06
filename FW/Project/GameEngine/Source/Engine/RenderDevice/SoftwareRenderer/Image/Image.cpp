//--------------------------------------------------
// File:    Image.cpp
// Created: 28/04/2013 12:12:02
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "Image.h"

CImageF32::CImageF32()
{
	m_Fmt = Renderer::IMGFMT_R32G32B32A32_FLOAT;
}

CImage8888 CImageF32::ToImage8888()
{
	CImage8888 result;

	result.Resize(m_Width, m_Height);
	for(uint32_t i=0; i< m_Width * m_Height; ++i)
	{
		result.GetRawData()[i] = glm::u32_rgba_cast(m_Data[i]);
	}

	return result;
}

CImage8888::CImage8888()
{
	m_Fmt = Renderer::IMGFMT_R8G8B8A8_UNORM;
}

CImage8888::~CImage8888()
{

}
