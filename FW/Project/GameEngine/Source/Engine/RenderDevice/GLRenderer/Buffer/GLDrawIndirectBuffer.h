#pragma once

#ifndef GLDrawIndirectBuffer_h__
#define GLDrawIndirectBuffer_h__

#include "GLVertexBuffer.h"

struct GLDrawElementsIndirectCommand
{
	GLuint	VertexCount;
	GLuint	InstanceCount;
	GLuint	FirstIndex;
	GLuint	BaseVertex;
	GLuint	BaseInstance;

	GLDrawElementsIndirectCommand(uint32_t vertexCount, uint32_t instanceCount)
		: VertexCount(vertexCount),
		InstanceCount(instanceCount),
		FirstIndex(0),
		BaseVertex(0),
		BaseInstance(0)
	{}
};

template <class T>
class CGLDrawIndirectBuffer : public CGLCommonBuffer
{
public:
	virtual GLuint	TargetType() const { return GL_DRAW_INDIRECT_BUFFER; }

	void			SetData(const vector<T>& data);
	void			Draw();
};

template <class T>
void CGLDrawIndirectBuffer<T>::SetData(const vector<T>& data)
{
	if (m_BufferHandle == 0)
	{
		glGenBuffers(1, &m_BufferHandle);
	}

	glBindBuffer(TargetType(), m_BufferHandle);
	glBufferData(TargetType(), sizeof(T)* data.size(), &data[0],
		MapToGLBufferUsage(m_BufferUsage));
}

template <class T>
void CGLDrawIndirectBuffer<T>::Draw()
{
	// VAO is binded when we called IB.SetBuffer()
	//Global().Renderer().BindVertexArray();

	glBindBuffer(TargetType(), m_BufferHandle);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0);
}


#endif // GLDrawIndirectBuffer_h__
