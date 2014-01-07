// local includes //////////////////////////////////
#include "stdafx.h"
#include "GLConstantBuffer.h" 

// defines /////////////////////////////////////////
CGLConstantBufferBase::CGLConstantBufferBase()
{

}

CGLConstantBufferBase::~CGLConstantBufferBase()
{
	if(m_BufferHandle)
	{
		glDeleteBuffers(1, &m_BufferHandle);
	}
}

void CGLConstantBufferBase::SetBuffer()
{
	// Attach the buffer to UBO binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, m_InputSlot, m_BufferHandle);
}


