//--------------------------------------------------
// File:    InputManager.cpp
// Created: 18/03/2013 09:13:26
//
// Description: $
//
//--------------------------------------------------

// local includes //////////////////////////////////
#include "stdafx.h"
#include "InputManager.h" 

#include "Core/CoreCpp.h"

CInputManager::CInputManager(HWND hwnd)
: m_hwnd(hwnd),
m_CurrCursorPosition(0, 0, 0),
m_PrevCursorPosition(0, 0, 0)
{
	memset(m_CurrKeyState, 0, sizeof(m_CurrKeyState));
}

void CInputManager::Update()
{
	// store key states
	memcpy(m_PrevKeyState, m_CurrKeyState, sizeof(m_CurrKeyState));
	for(int i=0;i<256;++i)
	{
		m_CurrKeyState[i] = GetAsyncKeyState(i) & 0x8000 ? 1 : 0;
	}
	
	// store cursor state
	m_PrevCursorPosition = m_CurrCursorPosition;
	POINT clientPos;
	if (GetCursorPos(&clientPos))
	{
		if (ScreenToClient(m_hwnd, &clientPos))
		{
			m_CurrCursorPosition[0] = (float)clientPos.x;
			m_CurrCursorPosition[1] = (float)clientPos.y;
		}
	}
}

bool CInputManager::KeyDown( uint8_t val ) const
{
	return (m_CurrKeyState[val] == true);
}

bool CInputManager::KeyUp( uint8_t val ) const
{
	return !KeyDown(val);
}

bool CInputManager::KeyPressed( uint8_t val ) const
{
	return (m_PrevKeyState[val] == false) && (m_CurrKeyState[val] == true);
}

bool CInputManager::KeyReleased( uint8_t val ) const
{
	return (m_PrevKeyState[val] == true) && (m_CurrKeyState[val] == false);
}

bool CInputManager::LeftMouseDown() const
{
	return KeyDown(VK_LBUTTON);
}

bool CInputManager::LeftMousePressed() const
{
	return KeyPressed(VK_LBUTTON);
}

bool CInputManager::LeftMouseReleased() const
{
	return KeyReleased(VK_LBUTTON);
}

bool CInputManager::RightMouseDown() const
{
	return KeyDown(VK_RBUTTON);
}

bool CInputManager::RightMousePressed() const
{
	return KeyPressed(VK_RBUTTON);
}

bool CInputManager::RightMouseReleased() const
{
	return KeyReleased(VK_RBUTTON);
}


// eof /////////////////////////////////////////////
