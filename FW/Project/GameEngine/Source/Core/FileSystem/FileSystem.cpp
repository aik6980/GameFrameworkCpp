#include "stdafx.h"
#include "FileSystem.h"
#include "Shlwapi.h"

// paths to useful place
namespace FileSystem
{
	fs::path g_ExecPath;
	fs::path GetExecutionPath()
	{
		if(g_ExecPath.empty())
		{
			wchar_t exec_path[MAX_PATH];
			DWORD length = GetModuleFileName( NULL, exec_path, MAX_PATH );
			PathRemoveFileSpec(exec_path);

			g_ExecPath = fs::path(exec_path);
		}
		return g_ExecPath;
	}

	fs::path GetResourcesPath()
	{
		fs::path execPath = GetExecutionPath();
		std::wstring resPathStr = TEXT("/Resources");

		// check up one level
		fs::path fullPath = fs::path(execPath.parent_path().wstring() + resPathStr);
		if(fs::exists(fullPath))
			return fullPath;

		// check up two level
		fullPath = fs::path(execPath.parent_path().parent_path().wstring() + resPathStr);
		if(fs::exists(fullPath))
			return fullPath;

		// all failed
		return TEXT("");
	}

	fs::path RelativePath( const fs::path &path, const fs::path &relative_to )
	{
		// create absolute paths
		fs::path p = fs::absolute(path);
		fs::path r = fs::absolute(relative_to);

		// if root paths are different, return absolute path
		if( p.root_path() != r.root_path() )
			return p;

		// initialize relative path
		fs::path result;

		// find out where the two paths diverge
		fs::path::const_iterator itr_path = p.begin();
		fs::path::const_iterator itr_relative_to = r.begin();
		while( *itr_path == *itr_relative_to && itr_path != p.end() && itr_relative_to != r.end() ) {
			++itr_path;
			++itr_relative_to;
		}

		// add "../" for each remaining token in relative_to
		if( itr_relative_to != r.end() ) {
			++itr_relative_to;
			while( itr_relative_to != r.end() ) {
				result /= "..";
				++itr_relative_to;
			}
		}

		// add remaining path
		while( itr_path != p.end() ) {
			result /= *itr_path;
			++itr_path;
		}

		return result;
	}


	// static initializer for lookup path
	static vector<std::wstring> s_GameResourcePaths[] =
	{
		list_of( L"" ),
		list_of(L"/Shaders/")(L"/Shaders/bin/")(L"/Shaders/src/")(L"/Shaders/fx/")(L"/Scripts/"),
		list_of( L"" ),
		list_of( L"" )
	};

	fs::path CGamePath::GetResourcePath( std::wstring fnStr, eGameResourceType type )
	{
		// use type as an index, make sure it is not out of bounds
		Debug::Assert( type < CGamePath::MAX , "[error] array out of bound");

		fs::path execPath = GetResourcesPath();
		vector<std::wstring>& resPathStr = s_GameResourcePaths[type];

		fs::path fullPath;
		for( int i=0; i < (int)resPathStr.size(); ++i)
		{
			fullPath = fs::path(execPath.wstring() + resPathStr[i] + fnStr);
			if(fs::is_regular_file(fullPath))
			{
				Debug::Print((boost::wformat(TEXT("path found %s")) % fullPath.wstring()).str());
				return fullPath;
			}
		}

		Debug::Print((boost::wformat(TEXT("path not found %s")) % fullPath.wstring()).str());
		return fs::path(TEXT(""));
	}
}
