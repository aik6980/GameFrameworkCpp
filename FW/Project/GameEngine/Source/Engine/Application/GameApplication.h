#pragma once
#ifndef GameApplication_h__
#define GameApplication_h__

#include "BaseApplication.h"

class CGameApplication : public CBaseApplication
{
public:
	// entry point
	static int Run(int numArgs, char** args);

	// game interface
	virtual void OnInit(int numArgs, char** args)=0;
	virtual void OnUpdate() {};
	virtual void OnTerminate() {};
protected:
	bool m_bRunning;
};

#endif // GameApplication_h__