#pragma once
#include <d3dx9.h>
#include "MContent.h"
#include "MGraphic.h"
#include "MKeyboard.h"
class Bat
{
	LPDIRECT3DTEXTURE9 img;
public:
	Bat(void);
	D3DXVECTOR2 position;
	float speed;	
	RECT rect;
	~Bat(void);
	void Init(MContent* content);
	void Update(float gameTime,MKeyboard* key);
	void Render(MGraphic* graphic);
};

