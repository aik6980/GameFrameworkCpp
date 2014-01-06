#include "stdafx.h"
#include "LuaHelper.h"

#include "stl/STLHelper.h"

LuaHelper::LuaHelper()
{
	m_pLuaState = NULL;
}

LuaHelper::~LuaHelper()
{
	Destroy();
}


void LuaHelper::ErrorString( lua_State* L, int status )
{
	if(status != Lua::LUA_OK)
	{
		Debug::Print((boost::format("Lua error: %1% %2% %3% %4%") % status % lua_tostring(L, -1) 
			% __FILE__ % __LINE__).str());
		lua_pop(L, 1);
	}
}

void LuaHelper::Initialize()
{
	m_pLuaState = lua_open();
	luaL_openlibs(m_pLuaState);
}

void LuaHelper::Destroy()
{
	lua_close(m_pLuaState);
}

void LuaHelper::OpenAndProcessFile( wstring fileName )
{
	string strfn = CSTLHelper::String(fileName);
	int s = luaL_loadfile(m_pLuaState, strfn.c_str());

	if(s == Lua::LUA_OK)
	{
		s = lua_pcall(m_pLuaState, 0, LUA_MULTRET, 0);
	}
	else
	{
		ErrorString(m_pLuaState, s);
	}
}

std::wstring LuaHelper::GetGlobalStringFromName( wstring varName )
{
 	wstring out = TEXT("");

	lua_getglobal(m_pLuaState, CSTLHelper::String(varName).c_str());
	if(lua_isstring(m_pLuaState, -1))
	{
		out = CSTLHelper::WString(lua_tostring(m_pLuaState, -1));
	}
	lua_pop(m_pLuaState, 1);

 	return out;
}

void LuaHelper::GetGlobalVector4FromName( vector<float>& oVal, wstring varName )
{
	oVal.resize(4);

	lua_getglobal(m_pLuaState, CSTLHelper::String(varName).c_str());
	if(lua_istable(m_pLuaState, -1))
	{
		for(int i=0; i<4; ++i)
		{
			lua_rawgeti(m_pLuaState, -1, i+1);
			oVal[i] = static_cast<float>(lua_tonumber(m_pLuaState, -1));
			lua_pop(m_pLuaState, 1);
		}
	}
	lua_pop(m_pLuaState, 1);
}


