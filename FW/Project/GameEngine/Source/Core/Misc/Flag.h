#pragma once
#ifndef Flag_h__
#define Flag_h__

#include <stdint.h>

template<typename TEnum>
class CFlagSet
{
public:
	inline void Set(const TEnum flag)		{ m_Data |= flag; }
	inline void Remove(const TEnum flag)	{ m_Data &= ~flag; }
	inline bool Test(const TEnum flag)		{ return (m_Data & flag) != 0; }
private:
	uint32_t m_Data;
};

#endif // Flag_h__