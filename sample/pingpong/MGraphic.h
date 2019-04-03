#pragma once
#include <d3d9.h>
#include <d3dx9.h>


class MGraphic
{
private:

	//doi tuong direct x
	LPDIRECT3D9 d3d;
	//thiet bi ve
	LPDIRECT3DDEVICE9 d3ddev;
	//Ve texture
	LPD3DXSPRITE d3dxSprite;
	//ve text

	//hwnd cua cua so ve
	HWND hWnd;
	int Width;
	int Height;
public:
	bool InitD3D();
	MGraphic(HWND, int, int);
	~MGraphic(void);
	void Begin();
	void End();
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DCOLOR color);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 postion, D3DCOLOR color);
	void DrawString(char* str);
	void DrawSurface();
	LPDIRECT3DDEVICE9 GetDevice();
};

