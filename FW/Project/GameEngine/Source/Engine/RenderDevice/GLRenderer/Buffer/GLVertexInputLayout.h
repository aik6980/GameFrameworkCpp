//--------------------------------------------------
// File:    GLVertexDecl.h
// Created: 27/12/2013 16:07:37
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLVERTEXDECL_H__2013_12_27_16_07_37
#define _GLVERTEXDECL_H__2013_12_27_16_07_37

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////
#include "Core/Core.h"
#include "RenderDevice/Renderer.h"
#include "RenderDevice/GLRenderer/GLDefines.h"

// forward declarations ////////////////////////////

// type declarations (enum struct class) /////////
struct CGLVertexInputElem
{
	string					Name;
	uint32_t				LayoutLocation;
	Renderer::DataFormat	Fmt;
	uint32_t				InputSlot;
	uint32_t				InstanceDataStepRate;
	uint32_t				AlignedBytesOffset;
};

class CGLVertexInputLayout
{
public:
	CGLVertexInputLayout();

	void AddElement(string name, uint32_t layoutLocation, Renderer::DataFormat fmt, uint32_t inputSlot, uint32_t instance_data_step_rate = 0);
	
	const GLuint						VAO()	const { return m_VAO; }
	const vector<CGLVertexInputElem>&	Elems() const { return m_IADesc; }
private:
	GLuint						m_VAO;
	vector<CGLVertexInputElem>	m_IADesc;

	uint32_t					m_OffsetInBytesToLastElem;
};

// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLVERTEXDECL_H__2013_12_27_16_07_37