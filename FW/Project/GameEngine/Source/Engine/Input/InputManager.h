#pragma once
#ifndef InputManager_h__
#define InputManager_h__

class CInputManager
{
public:
	CInputManager(HWND hwnd);

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

	glm::vec3	CursorPosition() const	{ return m_CurrCursorPosition; }
	glm::vec3	CursorVelocity() const	{ return m_CurrCursorPosition - m_PrevCursorPosition; }
private:
	bool m_CurrKeyState[256];
	bool m_PrevKeyState[256];

	glm::vec3	m_CurrCursorPosition;
	glm::vec3	m_PrevCursorPosition;

	HWND m_hwnd;
};

#endif // InputManager_h__