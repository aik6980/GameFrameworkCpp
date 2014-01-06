#pragma once
#ifndef Memory_h__
#define Memory_h__

#include <malloc.h>

/*
// declare the placement new
void* operator new (size_t size, size_t alignment);
void operator delete (void* ptr, size_t alignment); // cannot be explicitly called by user, only call when the exception throw

// override global new (everything will be aligned on 16 bytes)
void* operator new (size_t size)
{
	void* p = _aligned_malloc(size, 16);
	if(p==nullptr)
	{
		throw std::bad_alloc();
	}
	return p;
}

void operator delete (void* p)
{
	_aligned_free(p);
}

void* operator new[] (size_t size)
{
	void* p = _aligned_malloc(size, 16);
	if(p==nullptr)
	{
		throw std::bad_alloc();
	}
	return p;
}

void operator delete[] (void* p)
{
	_aligned_free(p);
}

// here is the base class for everything that is needed to aligned
template< int T >
class CMemAlign
{
public:
	void* operator new (size_t size)
	{
		return _aligned_malloc(size, T);
	}

	void operator delete (void* ptr)
	{
		_aligned_free(ptr);
	}
};

typedef CMemAlign<8>  CMemAlign8;	
typedef CMemAlign<16> CMemAlign16;
*/

#endif // Memory_h__