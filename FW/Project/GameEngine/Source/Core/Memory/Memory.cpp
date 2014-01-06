#include "stdafx.h" 
#include "Memory.h"

void* operator new (size_t size, size_t alignment)
{
	return _aligned_malloc(size, alignment);
}

void operator delete (void* ptr, size_t alignment)
{
	_aligned_free(ptr);
}