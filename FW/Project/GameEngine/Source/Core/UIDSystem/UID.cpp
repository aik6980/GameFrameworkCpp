#include "stdafx.h" 
#include "Core/UIDSystem/UID.h"

namespace UID
{
	UID32 UNASSIGNED_UID32 = 0xffffffff;

	UID32 CalcUID( const std::wstring& _src )
	{
		return boost::hash_value(_src);
	}
}

CHashString::CHashString()
{
	m_strUID = TEXT("");
	m_iUID = UID::UNASSIGNED_UID32;
}

CHashString::CHashString( const std::wstring& _src )
{
	m_strUID = _src;
	m_iUID = UID::CalcUID(m_strUID);
}

std::wstring CHashString::ToString()
{
	boost::wformat oStr;
	oStr = boost::wformat( TEXT("hash: %1%, %2%") ) 
		% m_iUID % m_strUID;

	return oStr.str();
}

void CHashString::Print()
{
	Debug::Print(ToString());
}

void CHashString::RunTest()
{
	// test hash string
	{
		CHashString testString(TEXT("hello world"));
		testString.Print();
		CHashString testString1(TEXT("helloworld"));
		testString1.Print();
	}	
}
