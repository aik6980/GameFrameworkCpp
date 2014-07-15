#pragma once
#ifndef WinGameApplication_h__
#define WinGameApplication_h__

#include "Lib/Win32++/wincore.h"
#include "GameApplication.h"

class CWinGameApplication : public CGameApplication, public CWinApp, public CWnd
{
public:
	CWinGameApplication()
		: m_CmdLineMode(false)
	{}

	// entry point
	static int Run(int numArgs, char** Args);

	// overridden winapp
	virtual int		MessageLoop();

	virtual void	InitWindow(int numArgs, char** Args);
protected:
	// overriden cwnd
	virtual void	PreCreate(CREATESTRUCT& cs);
	virtual LRESULT WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool m_CmdLineMode;
private:
	
};


#endif // WinGameApplication_h__


