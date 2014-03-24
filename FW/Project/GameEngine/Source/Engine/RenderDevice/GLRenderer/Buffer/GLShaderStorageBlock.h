#ifndef GLShaderStorageBlock_h__
#define GLShaderStorageBlock_h__

#include "GLBuffer.h"

class CGLShaderStorageBlockRaw : public CGLBufferBase
{
public:
	void	SetDataOffset(void* pData, uint32_t size);
};

template<class T>
class CGLShaderStorageBlock : public CGLBufferBase
{
public:
	void	InitData(const T& data);
};

#endif // GLShaderStorageBlock_h__
