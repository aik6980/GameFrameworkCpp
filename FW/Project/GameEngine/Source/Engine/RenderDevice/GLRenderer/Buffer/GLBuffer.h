#ifndef GLBuffer_h__
#define GLBuffer_h__

#include "RenderDevice/GLRenderer/GLDefines.h"

class CGLBufferBase
{
public:
	CGLBufferBase()
		: m_BufferHandle(0),
		m_InputSlot(0),
		m_BufferType(GL_ARRAY_BUFFER),
		m_Usage(GL_STATIC_DRAW)
	{}

	virtual ~CGLBufferBase();

	void		CreateBuffer(const uint32_t sizeInBytes);
	void		SetDataRaw(const void* pData, const uint32_t sizeInBytes, const uint32_t offset);

	void		SetBuffer();
	void		InputSlot(uint32_t val) { m_InputSlot = val; }
protected:
	GLuint		m_BufferHandle;
	uint32_t	m_InputSlot;

	GLenum		m_BufferType;
	GLenum		m_Usage;
};

#endif // GLBuffer_h__
