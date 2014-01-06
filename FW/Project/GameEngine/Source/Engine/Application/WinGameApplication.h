#pragma once
#ifndef WinGameApplication_h__
#define WinGameApplication_h__

#include "Lib/Win32++/wincore.h"
#include "GameApplication.h"

class CWinGameApplication : public CGameApplication, public CWinApp, public CWnd
{
public:
	// entry point
	static int Run(int numArgs, char** Args);

	// overridden winapp
	virtual BOOL InitInstance();
	virtual int MessageLoop();

	// overriden cwnd
protected:
	virtual void PreCreate(CREATESTRUCT& cs);
	virtual LRESULT WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
};


#endif // WinGameApplication_h__


