#ifndef GLResourceView_h__
#define GLResourceView_h__

class CGLResourceView
{
public:
	void	SetBuffer(uint32_t bufferHandle) { m_BufferHandle = bufferHandle; }
	void	Bind()
	{
		// Attach the buffer to the binding point
		glBindBufferBase(m_ResourceType, m_Slot, m_BufferHandle);
	}

protected:
	CGLResourceView(GLenum resType, uint32_t slot)
		: m_ResourceType(resType)
		, m_Slot(slot)
		, m_BufferHandle(0)
	{}

	GLenum	m_ResourceType;
	GLuint	m_Slot;

	// [NOTE] wonder if it is better to use weak_ptr<>
	GLuint	m_BufferHandle;
};

class CGLSSBOView : public CGLResourceView
{
public:
	CGLSSBOView(uint32_t slot)
		: CGLResourceView(GL_SHADER_STORAGE_BUFFER, slot)
	{}
};

class CGLAtomicCounterView : public CGLResourceView
{
public:
	CGLAtomicCounterView(uint32_t slot)
		: CGLResourceView(GL_ATOMIC_COUNTER_BUFFER, slot)
	{}
};

#endif // GLResourceView_h__
