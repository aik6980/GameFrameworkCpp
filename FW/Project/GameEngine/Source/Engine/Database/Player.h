#pragma once
#ifndef Player_h__
#define Player_h__

#include "GameObject.h"

class CPlayer : public CBaseGameObject
{
public:
	static CPlayer* CreateObject();

	virtual void Update();
private:
};

#endif // Player_h__