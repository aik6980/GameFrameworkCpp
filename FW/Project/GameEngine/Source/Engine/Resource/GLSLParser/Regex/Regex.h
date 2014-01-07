#pragma once
#ifndef Regex_h__
#define Regex_h__

#include <vector>
#include <string>

using namespace std;

#include <boost/regex.hpp>

bool regex_search1(const string& source, const string& expr, vector<string>& results);
bool regex_search2(const string& source, const string& expr, vector<string>& results, vector<string>& results2);

#endif // Regex_h__