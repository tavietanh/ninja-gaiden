#include "MGraphic.h"

MGraphic::MGraphic(HWND hwnd, int W, int H)
{
	this->hWnd = hwnd;
	this->Width = W;
	this->Height = H;
	this->d3d = NULL;
	this->d3ddev = NULL;
	this->d3dxSprite = NULL;
}

bool MGraphic::InitD3D()
{
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!this->d3d)
		return false;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = this->Width;
	d3dpp.BackBufferHeight = this->Height;
	d3dpp.hDeviceWindow = this->hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	HRESULT hr = this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		this->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddev);
	if (FAILED(hr))
	{
		return false;
	}
	hr = D3DXCreateSprite(this->d3ddev, &this->d3dxSprite);
	if (FAILED(hr))
		return false;
	return true;
}

MGraphic::~MGraphic(void)
{
}

void MGraphic::Begin()
{
	this->d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 105, 180), 1, NULL);
	this->d3ddev->BeginScene();
	this->d3dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void MGraphic::End()
{
	this->d3dxSprite->End();
	this->d3ddev->EndScene();
	this->d3ddev->Present(NULL, NULL, NULL, NULL);
}
void MGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DCOLOR color)
{
	this->d3dxSprite->Draw(texture, NULL, NULL, &D3DXVECTOR3(postion.x, postion.y, 0), color);
}


void MGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 postion, D3DCOLOR color)
{
	this->d3dxSprite->Draw(texture, &source, NULL, &D3DXVECTOR3(postion.x, postion.y, 0), color);
}

void MGraphic::DrawSurface()
{
}

LPDIRECT3DDEVICE9 MGraphic::GetDevice()
{
	return this->d3ddev;
}

void MGraphic::DrawString(char* str)
{
}