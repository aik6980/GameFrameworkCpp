#pragma once
#ifndef MainView_h__
#define MainView_h__

#include "RenderView.h"

class CMainView : public CBaseRenderView
{
public:
	CMainView() : CBaseRenderView(MAINGAME_VIEW) {};

	virtual void Render(CGLDevice& context);
private:
};

#endif // MainView_h__