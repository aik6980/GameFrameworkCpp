#pragma once
#ifndef STLDefines_h__
#define STLDefines_h__

#include "TargetDefines.h"

#include <climits>
#include <cfloat>
#include <cstdint>

// standard unit
#include <cstdint>

#include <string>
#include <iostream>
#include <sstream>

#include <vector>
#include <bitset>

// for C++0x
// include for hash version of map/multimap
#include <array>
#include <memory>
#include <unordered_map>

using namespace std;

// find the offset of the class member
// Note: __w64 unsigned int -> DWORD, which support /Wp64
//		need to be changed in order to match the compiler
#define	OFFSET_OF(structName,memberName)\
	((__w64 unsigned int)(&((structName*)0)->memberName))

// find the number of element
// Note: use on static array only
#define NUM_ELEM(static_array)\
	(sizeof(static_array)/sizeof(static_array[0]))

// alignment
#define KW_DECL_ALIGNED(x)	__declspec( align( x) )

// safe delete function
template<typename T>
void Safe_Delete(T pObj)
{
	if(pObj)
	{
		delete pObj;
		pObj = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T pArray)
{
	if(pArray)
	{
		delete[] pArray;
		pArray = nullptr;
	}
}

template<typename TVal, typename TContainer, typename TKey>
TVal FindInMap(TContainer& container, const TKey& key)
{
	TContainer::iterator itr = container.find(key);
	if(itr != end(container))
	{
		return itr->second;
	}

	return nullptr;
}

// Flags
typedef std::bitset<8> FLAGS8;

#endif // STLDefines_h__