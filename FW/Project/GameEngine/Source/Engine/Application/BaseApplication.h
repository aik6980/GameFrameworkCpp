#pragma once
#ifndef BaseApplication_h__
#define BaseApplication_h__

#include "BaseApplicationMacros.h"

class CBaseApplication
{
public:
	typedef int (*EntryPoint)(int, char**);
	static EntryPoint Run;
protected:
	CBaseApplication() {}

	static bool ms_bInitializeRegistered;
	static CBaseApplication* INSTANCE;
};

#endif // BaseApplication_h__