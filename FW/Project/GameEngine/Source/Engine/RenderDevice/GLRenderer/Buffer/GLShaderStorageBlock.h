#ifndef GLShaderStorageBlock_h__
#define GLShaderStorageBlock_h__

#include "GLBuffer.h"

template<class T>
class CGLShaderStorageBlock : public CGLBufferBase
{
public:
	CGLShaderStorageBlock();

	void	InitData(const T& data);
};

#endif // GLShaderStorageBlock_h__
