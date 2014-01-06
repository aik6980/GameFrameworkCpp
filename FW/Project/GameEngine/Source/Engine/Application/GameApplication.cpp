#include "stdafx.h" 
#include "GameApplication.h"

int CGameApplication::Run( int numArgs, char** args )
{
	// the magic macro with create the correct class for us
	CGameApplication* game = static_cast<CGameApplication*>(INSTANCE);

	// initialization
	game->OnInit(numArgs,args);

	while(game->m_bRunning)
	{
		game->OnUpdate();
	}

	game->OnTerminate();

	return 0;
}