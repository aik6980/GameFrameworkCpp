#include "stdafx.h" 
#include "WinGameApplication.h"
#include "RenderDevice/RenderDeviceCpp.h"

int CWinGameApplication::Run( int numArgs, char** Args )
{
	((CWinGameApplication*)INSTANCE)->m_bRunning = true;
	return ((CWinGameApplication*)INSTANCE)->CWinApp::Run();
}

BOOL CWinGameApplication::InitInstance()
{
	// create main windows
	CWnd::Create();

	OnInit(0, NULL);
	// Win32++ return TRUE on successful
	return TRUE;
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
	// set windows size
	cs.cx = Renderer::SCREEN_WIDTH;
	cs.cy = Renderer::SCREEN_HEIGHT; 
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