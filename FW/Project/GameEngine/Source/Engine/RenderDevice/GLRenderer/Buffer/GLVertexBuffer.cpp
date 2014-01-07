//--------------------------------------------------
// File:    GLVertexBuffer.cpp
// Created: 09/12/2013 21:58:55
//
// Description: $
//

//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "GLVertexBuffer.h"

#include "Core/CoreCpp.h"
#include "Global.h"
#include "RenderDevice/GLRenderer/GLDevice.h"

// defines /////////////////////////////////////////
GLuint CGLCommonBuffer::MapToGLBufferUsage( BufferUsageEnum e )
{
	switch(e)
	{
		case STATIC_DRAW	:	return GL_STATIC_DRAW;
		case DYNAMIC_DRAW	:	return GL_DYNAMIC_DRAW;
		default:
			Debug::Print("Unsupported case \n");
			return GL_STATIC_DRAW;
	}
}


CGLCommonBuffer::~CGLCommonBuffer()
{
	if(m_BufferHandle)
	{
		glInvalidateBufferData(m_BufferHandle);
		glDeleteBuffers(1, &m_BufferHandle);
	}
}

void CGLVertexBufferCommon::SetBuffer()
{
	Global::Renderer().SetVertexBuffer(*this, m_InputSlot);
}

