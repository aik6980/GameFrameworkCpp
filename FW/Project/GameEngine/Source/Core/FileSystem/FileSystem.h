#pragma once
#ifndef FileSystem_h__
#define FileSystem_h__

#include "TargetDefines.h"

// include win32 header here for TEXT() macro
#include <Windows.h>

#include "STL/STLDefines.h"
#include "Boost/BoostDefines.h"
#include "Debug/DebugPrint.h"

namespace FileSystem
{
	fs::path GetExecutionPath();
	fs::path GetResourcesPath();

	class CGamePath
	{
	public:
		enum eGameResourceType
		{
			ALL = 0,
			SHADERS,
			TEXTURES,
			MODELS,
			MAX
		};

		static fs::path GetResourcePath(std::wstring fnStr, eGameResourceType type = ALL);
	};
};

#include "FileSystem.inl"
#endif // FileSystem_h__