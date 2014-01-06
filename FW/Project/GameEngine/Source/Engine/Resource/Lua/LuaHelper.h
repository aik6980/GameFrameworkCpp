#pragma once
#ifndef LuaHelper_h__
#define LuaHelper_h__

#include "Core.h"
#include "LuaDefines.h"

namespace Lua
{
	enum
	{
		LUA_OK = 0,
	};
}

class LuaHelper
{
public:
	LuaHelper();
	~LuaHelper();

	void Initialize();
	void Destroy();

	void OpenAndProcessFile(wstring fileName);
	wstring GetGlobalStringFromName(wstring varName);
	
	void GetGlobalVector4FromName(vector<float>& oVal, wstring varName);
	
	void ErrorString(lua_State* L, int status);

	void TestRun();
private:
	lua_State* m_pLuaState;
};

#endif // LuaHelper_h__