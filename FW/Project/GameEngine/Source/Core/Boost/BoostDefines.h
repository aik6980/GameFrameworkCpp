#pragma once
#ifndef BoostDefines_h__
#define BoostDefines_h__ 

#include "TargetDefines.h"

// boost library linker
#ifdef BUILD_DEBUG
	#if _INTELCOMPILER_
		#pragma comment(lib, "libboost_filesystem-iw-mt-gd.lib")
	#elif _VC2010COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc100-mt-gd-1_52.lib")
	#elif _VC2012COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc110-mt-gd-1_53.lib")
	#elif _VC2013COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc120-mt-gd-1_55.lib")
	#endif
#else
	#if _INTELCOMPILER_
		#pragma comment(lib, "libboost_filesystem-iw-mt.lib")
	#elif _VC2010COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc100-mt-1_52.lib")
	#elif _VC2012COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc110-mt-1_53.lib")
	#elif _VC2013COMPILER_
		#pragma comment(lib, "libboost_filesystem-vc120-mt-1_55.lib")
	#endif
#endif

// boost
#include <boost/bind.hpp>

// boost assign
// Note: 
//  - allow an alternative neat way of initialization STL container
//
#include <boost/assign.hpp>
using namespace boost::assign;

// boost filesystem
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

// boost assignment helper
// - for array initialization
#include <boost/assign.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_of.hpp>

// boost C-array wrapper
#include <boost/array.hpp>

// boost string formatter
#include <boost/format.hpp>

// boost lambda
#include <boost/lambda/lambda.hpp>

// boost hash
#include <boost/functional/hash.hpp>

// boost string algorithm
#include <boost/algorithm/string.hpp>


#endif // BoostDefines_h__