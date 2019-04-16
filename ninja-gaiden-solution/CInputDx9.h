#ifndef CINPUTDX9_H
#define CINPUTDX9_H

#include "FrameworkDefine.h"
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

class CInputDx9
{
	//Manage Input of Game
	bool					m_PressKey[256];
	char					m_currentBuffer[256];
	char					m_previousBuffer[256];
	CInputDx9();
	D3DXVECTOR2				m_cursorLocation;
	DIDEVICEOBJECTDATA		m_KeyEvents[1024];
	DIMOUSESTATE2			m_mouseState;
	DIMOUSESTATE2			m_previousMouseState;
	LPDIRECTINPUT8			m_lpDirectInput;
	LPDIRECTINPUTDEVICE8	m_lpKeyBoardDevice;
	LPDIRECTINPUTDEVICE8	m_lpMouseDevice;
	static CInputDx9*		s_Instance;
public:
	bool					IsKeyDown(int keyCode);
	bool					IsKeyPress(int keyCode);
	bool					IsKeyRelease(int keyCode);
	bool					IsKeyUp(int keyCode);

	
	D3DXVECTOR2				GetCursorLocation();
	static CInputDx9*		getInstance();
	void					InitializeInput();
	void					InitializeKeyBoardDevice(HWND handleWindow);
	void					InitializeMouseDevice(HWND handleWindow);
	void					Release();
	void					SetKeyDown(int keyCode);
	void					SetKeyUp(int keyCode);
	void					UpdateKeyBoard();
	void					UpdateMouse();
	~CInputDx9();
};
#endif