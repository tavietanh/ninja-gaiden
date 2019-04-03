#pragma once
#include <dinput.h>
class MKeyboard
{
	LPDIRECTINPUT8 di8;
	LPDIRECTINPUTDEVICE8 did8;
	char key_buffer[256];
	HINSTANCE hInstance;
	HWND hWnd;
public:
	bool Init();
	MKeyboard(HINSTANCE hIns, HWND hwnd);
	void GetState();
	bool IsKeyDown(int Key);
	bool IsPreKeyDown(int Key);
	~MKeyboard(void);
};

