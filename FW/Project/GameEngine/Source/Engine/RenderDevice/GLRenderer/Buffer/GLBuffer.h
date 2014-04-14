#ifndef GLBuffer_h__
#define GLBuffer_h__

#include "RenderDevice/GLRenderer/GLDefines.h"

class CGLBufferGeneric
{
public:
	CGLBufferGeneric()
		: m_BufferHandle(0),
		m_BufferType(GL_ARRAY_BUFFER),
		m_Usage(GL_DYNAMIC_DRAW)
	{}

	~CGLBufferGeneric()
	{
		if (m_BufferHandle)
		{
			glDeleteBuffers(1, &m_BufferHandle);
		}
	}

	void		CreateBuffer(const uint32_t sizeInBytes);
	void		SetDataRaw(const void* pData, const uint32_t sizeInBytes, const uint32_t offset);

	template<class T>
	void		SetData(const vector<T>& data)
	{
		if (m_BufferHandle == 0)
		{
			CreateBuffer(data.size() * sizeof(T));
		}
	}
protected:
	GLuint		m_BufferHandle;
	GLenum		m_BufferType;
	GLenum		m_Usage;
};

#endif // GLBuffer_h__
