#include "Game.h"

Game::Game(HINSTANCE hIns, int W, int H, char* name)
{
	this->hInstance = hIns;
	this->Width = W;
	this->Height = H;
	this->hWnd = NULL;
	strcpy(this->windowName, name);
}

Game::~Game(void)
{
}

LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Game::InitWindow()
{
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIconSm = 0;
	wndclass.hIcon = 0;
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = this->hInstance;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = "Game";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndclass))
	{
		return false;
	}
	this->hWnd = CreateWindow("Game", this->windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, this->Width, this->Height, NULL, NULL, this->hInstance, NULL);
	if (!this->hWnd)
		return false;
	ShowWindow(this->hWnd, SW_NORMAL);
	UpdateWindow(this->hWnd);
	graphic = new MGraphic(this->hWnd, 600, 300);


	if (!graphic->InitD3D())
		return false;
	content = new MContent(graphic->GetDevice());
	return true;
}

void Game::InitGame()
{
	ball = new Ball();
	ball->Init(content);
	bat = new Bat();
	bat->Init(content);
	keyboard = new MKeyboard(hInstance, hWnd);
	keyboard->Init();
}

void Game::Update(float gameTime)
{
	ball->Update(gameTime);
	keyboard->GetState();
	bat->Update(gameTime, keyboard);

	// xet va cham voi bat
	if (Check(bat->rect, ball->rect))
	{
		ball->dx = -ball->dx;
	}
}
void Game::Render()
{
	graphic->Begin();
	ball->Render(graphic);
	bat->Render(graphic);
	graphic->End();
}
