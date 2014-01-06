#pragma once
#ifndef InputManager_h__
#define InputManager_h__

class CInputManager
{
public:
	CInputManager();

	void	Update();

	bool	KeyDown(uint8_t val) const;
	bool	KeyUp(uint8_t val) const;
	bool	KeyPressed(uint8_t val) const;
	bool	KeyReleased(uint8_t val) const;

	bool	LeftMouseDown() const;
	bool	LeftMousePressed() const;
	bool	LeftMouseReleased() const;

	bool	RightMouseDown() const;
	bool	RightMousePressed() const;
	bool	RightMouseReleased() const;
private:

	bool m_CurrKeyState[256];
	bool m_PrevKeyState[256];
};

#endif // InputManager_h__