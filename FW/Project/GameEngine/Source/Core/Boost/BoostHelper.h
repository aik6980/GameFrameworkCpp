#pragma once
#ifndef BoostHelpers_h__
#define BoostHelpers_h__

#include "BoostDefines.h"

namespace BoostHelper
{
	// for boost
	template<typename T>
	void SharePtr_AlignedMemDeleter(T* ptr)
	{
		// there is no "explicit" placement delete,
		// so this is a wrapper, and we have to call the destructor explicitly
		ptr->~T();
		_aligned_free(ptr);
	}

	template<typename T>
	boost::shared_ptr<T> CreateSharePtr(size_t alignment = 1)
	{
		return boost::shared_ptr<T>(new(alignment) T(), SharePtr_AlignedMemDeleter<T> ); 
	}
}

#endif // BoostHelpers_h__