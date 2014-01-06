//--------------------------------------------------
// File:    GLConstantBuffer.h
// Created: 28/12/2013 13:30:43
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLCONSTANTBUFFER_H__2013_12_28_13_30_41
#define _GLCONSTANTBUFFER_H__2013_12_28_13_30_41

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "RenderDevice/GLRenderer/GLDefines.h"


// type declarations (enum struct class) /////////
class CGLConstantBufferBase
{
public:
	CGLConstantBufferBase();
	virtual ~CGLConstantBufferBase();

	void		SetBuffer();
	void		InputSlot(uint32_t val) { m_InputSlot = val; }
protected:
	GLuint		m_BufferHandle;
	uint32_t	m_InputSlot;

};

template<class T>
class CGLConstantBuffer : public CGLConstantBufferBase
{
public:
	void		SetData(const T& data);
private:
	T			m_Data;
};

template<class T>
void CGLConstantBuffer<T>::SetData(const T& data )
{
	if(m_BufferHandle == 0)
	{
		glGenBuffers(1, &m_BufferHandle);
	}

	// only update data only if it's been changed
	if((m_Data == data) == false)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &data, GL_DYNAMIC_DRAW);
		m_Data = data;
	}
}

// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLCONSTANTBUFFER_H__2013_12_28_13_30_41