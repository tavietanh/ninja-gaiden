#pragma once
#include <Windows.h>
#include "MGraphic.h"
#include "MContent.h"
#include "MKeyboard.h"
#include "Ball.h"
#include "Bat.h"
#include "Collision.h"
//RSManager* RSManager::instance = NULL;
class Game
{
private:
	//hinstance 
	HINSTANCE hInstance;
	//hwnd
	HWND hWnd;
	//doi tuong direct x
	int Width;
	int Height;
	char windowName[256];


	static HRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



	//Khai báo đối tượng graphic
	MGraphic* graphic;
	//Khai báo đối tượng Content(Dùng để load dữ liệu)
	MContent* content;
	//Khai báo đối tượng Keyboard
	MKeyboard* keyboard;
	//Khai báo quả banh
	Ball* ball;
	//Khai báo vợt banh
	Bat* bat;
	Collision* collision;
	bool Check(RECT r1, RECT r2)
	{
		return !(r1.left + r1.right < r2.left || r1.top + r1.bottom < r2.top || r2.left + r2.right < r1.left || r2.top + r2.bottom < r1.top);
	}

public:
	bool InitWindow();
	void InitGame();
	void Update(float gameTime);
	void Render();
	Game(HINSTANCE hIns, int W, int H, char* name);
	~Game(void);
};
