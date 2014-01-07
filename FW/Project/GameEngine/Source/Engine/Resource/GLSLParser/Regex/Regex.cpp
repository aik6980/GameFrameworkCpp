#include "stdafx.h"
#include "Regex.h"

bool regex_search1( const string& source, const string& expr, vector<string>& results )
{
	const boost::regex r(expr);
	boost::smatch what;
	std::string::const_iterator start = source.begin();
	std::string::const_iterator end   = source.end();

	while (boost::regex_search(start, end, what, r))
	{
		string str(what[1].first, what[1].second);
		results.push_back(str);

		// Update the beginning of the range to the character
		// following the whole match
		start = what[0].second;
	}

	return true;
}

bool regex_search2( const string& source, const string& expr, vector<string>& results, vector<string>& results2 )
{
	const boost::regex r(expr);
	boost::smatch what;
	std::string::const_iterator start = source.begin();
	std::string::const_iterator end   = source.end();

	while (boost::regex_search(start, end, what, r))
	{
		{
			string str(what[1].first, what[1].second);
			results.push_back(str);
		}

		{
			string str(what[2].first, what[2].second);
			results2.push_back(str);
		}

		// Update the beginning of the range to the character
		// following the whole match
		start = what[0].second;
	}

	return true;
}

