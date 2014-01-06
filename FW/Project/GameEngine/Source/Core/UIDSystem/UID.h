#pragma once
#ifndef UID_h__
#define UID_h__

#include "Core.h"

// UID
namespace UID
{
	typedef unsigned long UID32;

	extern UID32 UNASSIGNED_UID32;

	UID32 CalcUID(const std::wstring& _src);
}

class CHashString
{
public:
	CHashString();
	CHashString(const std::wstring& _src);

	inline bool operator < (const CHashString& _rhs) const
	{
		return (m_iUID < _rhs.m_iUID); 
	}

	UID::UID32 GetUID32() const { return m_iUID; }

	void Print();
	std::wstring ToString();

	static void RunTest();
private:
	UID::UID32		m_iUID; 			
	std::wstring	m_strUID;
};

#endif // UID_h__