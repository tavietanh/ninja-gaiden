#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPTSTR a, int c)
{
	MSG msg;
	Game game(h,600,300,"PingPong");
	if(!game.InitWindow())
	{
		MessageBox(NULL,"Can't init game","Error",MB_OK);
		return 0;
	}
	//Load data
	game.InitGame();
	//
	LARGE_INTEGER startTime;
	LARGE_INTEGER frequence;
	float gameTime = 0;
	LARGE_INTEGER endTime ;
	float cntPerSecond = 0;	
	ZeroMemory(&msg,sizeof(msg));
	QueryPerformanceFrequency(&frequence);
	cntPerSecond = 1000.0f / (float)frequence.QuadPart;
	QueryPerformanceCounter(&endTime);
	float delay = 0;	
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&startTime);					
			game.Update(gameTime);
			game.Render();
			QueryPerformanceCounter(&endTime);
			gameTime = ((float)endTime.QuadPart - (float)startTime.QuadPart) * cntPerSecond ;	
		}
	}
	return 0;
}