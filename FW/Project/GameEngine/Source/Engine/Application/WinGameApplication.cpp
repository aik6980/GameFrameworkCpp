#include "stdafx.h" 
#include "WinGameApplication.h"
#include "RenderDevice/RenderDeviceCpp.h"

int CWinGameApplication::Run( int numArgs, char** Args )
{
	((CWinGameApplication*)INSTANCE)->m_bRunning = true;
	((CWinGameApplication*)INSTANCE)->InitWindow(numArgs, Args);

	return ((CWinGameApplication*)INSTANCE)->CWinApp::Run();
}

void CWinGameApplication::InitWindow(int numArgs, char** Args)
{
	if (numArgs>1)
	{
		Debug::Print("Start CmdLineMode");
		m_CmdLineMode = true;
		m_bRunning = false;
	}
	else
	{
		Debug::Print("Start GameMode");
	}

	// create main windows
	CWnd::Create();
	OnInit(numArgs, Args);
}

int CWinGameApplication::MessageLoop()
{
	MSG Msg = {0};
	while(m_bRunning)
	{
		if( Msg.message==WM_QUIT)
			m_bRunning = false;

		if( PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&Msg);
			::DispatchMessage(&Msg);
		}
		else
		{
			OnUpdate();
		}
	}

	// cleanup game
	OnTerminate();
	return LOWORD(Msg.wParam);
}

void CWinGameApplication::PreCreate( CREATESTRUCT& cs )
{
	if (m_CmdLineMode)
	{
		// set windows size
		cs.cx = cs.cy = 1;
		// set window style
		cs.style = WS_POPUP;
	}
	else
	{
		// set windows size
		cs.cx = Renderer::SCREEN_WIDTH;
		cs.cy = Renderer::SCREEN_HEIGHT;
	}
}

LRESULT CWinGameApplication::WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_DESTROY:
		::PostQuitMessage( 0 );
		break;

	case WM_SIZING:
		break;

	case WM_PAINT:
		break;
	}

	return WndProcDefault(uMsg, wParam, lParam);
}


