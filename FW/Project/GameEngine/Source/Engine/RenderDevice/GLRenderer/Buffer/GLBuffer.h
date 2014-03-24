#ifndef GLBuffer_h__
#define GLBuffer_h__

class CGLBufferBase
{
public:
	CGLBufferBase()
		: m_BufferHandle(0),
		m_InputSlot(0)
	{}

	virtual ~CGLBufferBase();

	void		SetBuffer();
	void		InputSlot(uint32_t val) { m_InputSlot = val; }
protected:
	GLuint		m_BufferHandle;
	uint32_t	m_InputSlot;

};

#endif // GLBuffer_h__
