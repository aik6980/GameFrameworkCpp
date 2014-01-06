//--------------------------------------------------
// File:    Player.cpp
// Created: 29/03/2013 20:34:42
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h" 
#include "Player.h" 

CPlayer* CPlayer::CreateObject()
{
	CPlayer* obj = new CPlayer();

	// register with sub systems

	return obj;
}

void CPlayer::Update()
{

}
