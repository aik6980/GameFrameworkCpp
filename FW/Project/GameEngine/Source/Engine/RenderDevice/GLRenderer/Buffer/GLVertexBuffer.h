//--------------------------------------------------
// File:    GLVertexBuffer.h
// Created: 09/12/2013 21:57:49
//
// Description: $
//

//--------------------------------------------------

#ifndef _GLVERTEXBUFFER_H__2013_12_09_21_57_48
#define _GLVERTEXBUFFER_H__2013_12_09_21_57_48

#pragma once

#ifdef SHOW_HEADERS
#pragma message(" < "__FILE__)
#endif // SHOW_HEADERS

// includes ////////////////////////////////////////
#include "GLVertexInputLayout.h"

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////
class CMeshData;
class CGLVertexInputLayout;

enum BufferUsageEnum
{
	STATIC_DRAW,
	DYNAMIC_DRAW
};

// type declarations (enum struct class) /////////
class CGLCommonBuffer
{
public:
	CGLCommonBuffer()
		: m_BufferHandle(0),
		m_BufferUsage(STATIC_DRAW)
	{}

	virtual ~CGLCommonBuffer();

	virtual GLuint TargetType() const = 0;
	GLuint	BufferHandle() const { return m_BufferHandle; }

	void	BufferUsage(const BufferUsageEnum val) { m_BufferUsage = val; }
protected:
	static GLuint	MapToGLBufferUsage(BufferUsageEnum e);

	BufferUsageEnum		m_BufferUsage;
	GLuint				m_BufferHandle;
};

class CGLVertexBufferCommon : public CGLCommonBuffer
{
public:
	CGLVertexBufferCommon()
		: m_InputSlot(0),
		m_Stride(0)
	{}

	virtual GLuint	TargetType		() const { return GL_ARRAY_BUFFER; };

	void			InputSlot(uint32_t val) { m_InputSlot = val; }
	uint32_t		Stride() const			{ return m_Stride; }

	void			SetBuffer		();
protected:
	uint32_t		m_InputSlot;
	uint32_t		m_Stride;
};

template<class T>
class CGLVertexBuffer : public CGLVertexBufferCommon
{
public:
	void			SetData			(const vector<T>& data);
private:
};

template<class T>
void CGLVertexBuffer<T>::SetData( const vector<T>& data )
{
	if (data.empty())
		return;

	if(m_BufferHandle == 0)
	{
		glGenBuffers( 1, &m_BufferHandle );
	}
	
	glBindBuffer(TargetType(), m_BufferHandle);
	glBufferData(TargetType(), sizeof(T) * data.size(), &data[0],
                    MapToGLBufferUsage(m_BufferUsage));
	
	m_Stride = sizeof(T);
}

template<class T>
class CGLIndexBuffer : public CGLCommonBuffer
{
public:
	CGLIndexBuffer()
		: m_NumIndices(0)
	{}

	virtual GLuint	TargetType		() const { return GL_ELEMENT_ARRAY_BUFFER; };
	void			SetData			(const vector<T>& data);

	void			SetBuffer();
	void			DrawInstancing	(const uint32_t numInstances);
private:
	uint32_t		m_NumIndices;
};

template<class T>
void CGLIndexBuffer<T>::SetBuffer()
{
	Global().Renderer().BindVertexArray();
	glBindBuffer(TargetType(), m_BufferHandle);
}

template<class T>
void CGLIndexBuffer<T>::SetData( const vector<T>& data )
{
	if(m_BufferHandle == 0)
	{
		glGenBuffers( 1, &m_BufferHandle );
	}

	glBindBuffer(TargetType(), m_BufferHandle);
	glBufferData(TargetType(), sizeof(T) * data.size(), &data[0],
                    MapToGLBufferUsage(m_BufferUsage));

	m_NumIndices = data.size();
}

template<class T>
void CGLIndexBuffer<T>::DrawInstancing( const uint32_t numInstances )
{
	Global().Renderer().BindVertexArray();

	glBindBuffer(TargetType(), m_BufferHandle);
	//glDrawElementsInstanced(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0, numInstances);
	glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0, numInstances,0, 0);
}

// eof /////////////////////////////////////////////

#ifdef SHOW_HEADERS
#pragma message(" > "__FILE__)
#endif // SHOW_HEADERS

#endif // _GLVERTEXBUFFER_H__2013_12_09_21_57_48