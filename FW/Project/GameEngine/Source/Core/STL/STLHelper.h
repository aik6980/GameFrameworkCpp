#pragma once
#ifndef STLHelper_h__
#define STLHelper_h__

#include "Core.h"

class CSTLHelper
{
public:
	// string conversion
	static wstring WString(const string &s, const locale &loc = locale());
	static string  String(const wstring &ws);
};

#endif // STLHelper_h__