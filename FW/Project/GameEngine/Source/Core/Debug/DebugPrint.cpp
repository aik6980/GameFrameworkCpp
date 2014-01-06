#include "stdafx.h"
#include "DebugPrint.h"

#include "STL/STLDefines.h"
#include <stdarg.h>
#include <assert.h>

// include win32 specific here for
// OutputDebugString()
#include <Windows.h>

const int g_debugStrBufferSize = 1024;
char g_debugStrBuffer[g_debugStrBufferSize] = {0};
void Debug::Print( const char* format, ... )
{	
	// get arguments
	// http://www.cplusplus.com/reference/clibrary/cstdarg/
	va_list argList;
	va_start(argList, format);

	vsprintf_s<g_debugStrBufferSize>(g_debugStrBuffer, format, argList);

#ifdef DEF_HAVECONSOLE
	cout << format;
#else
	OutputDebugStringA(format);
#endif

	va_end(argList);
}

std::string g_debugStrOut; 
void Debug::Print(const std::string& str )
{
	// automatically add \n
	g_debugStrOut = str + "\n";

#ifdef DEF_HAVECONSOLE
	cout << g_debugStrOut;
#else
	OutputDebugStringA(g_debugStrOut.c_str());
#endif

}

std::wstring g_debugWStrOut;
void Debug::Print( const std::wstring& wstr )
{
	// automatically add \n
	g_debugWStrOut = wstr + TEXT("\n");

#ifdef DEF_HAVECONSOLE
	wcout << g_debugWStrOut;
#else
	OutputDebugString(g_debugWStrOut.c_str());
#endif

}

void Debug::Print( const boost::format& strfmt )
{
	Debug::Print(strfmt.str());
}

void Debug::Print( const boost::wformat& strfmt )
{
	Debug::Print(strfmt.str());
}

void Debug::Assert( bool condition, std::string str )
{
	assert( condition );
}
