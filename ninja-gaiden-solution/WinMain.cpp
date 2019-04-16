#include "CGame.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{

	CGame* Run = new CGame();
	Run->Initialize(hInstance, true);
	Run->Run();
	Run->Exit();
	//SAFE_DELETE(Run);
	return 0;
}