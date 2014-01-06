#pragma once
#ifndef DebugPrint_h__
#define DebugPrint_h__

#include "TargetDefines.h"
#include "Boost/BoostDefines.h"

namespace Debug
{
	void Print(const char* format, ...);
	void Print(const std::string& str);
	void Print(const std::wstring& wstr);
	void Print(const boost::format& strfmt);
	void Print(const boost::wformat& strfmt);

	void Assert(bool condition, std::string str ); 
};

#endif // DebugPrint_h__