#include "stdafx.h" 
#include "STLHelper.h"

std::wstring CSTLHelper::WString(const std::string &s, const locale &loc)
{
	wstring out;
	out.reserve(s.size());
	transform(s.begin(), s.end(), back_inserter(out),
		boost::bind(&ctype<wchar_t>::widen,
		boost::ref(use_facet<ctype<wchar_t> >(loc)), _1));
	return out;
}

std::string CSTLHelper::String( const std::wstring &ws )
{
	// The following code is WINDOWS specific
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &ws[0], (int)ws.size(), NULL, 0, NULL, NULL);
	std::string strTo( size_needed, 0 );
	WideCharToMultiByte(CP_UTF8, 0, &ws[0], (int)ws.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}