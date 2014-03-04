#pragma once
#ifndef World_h__
#define World_h__

#include "Database/GameObject.h"

class CWorld
{
public:
	void	Initialize();
	void	Update();

private:
	vector<shared_ptr<CBaseGameObject>> m_GameObjects;
};

#endif // World_h__