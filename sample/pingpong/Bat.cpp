#include "Bat.h"


Bat::Bat(void)
{
}


Bat::~Bat(void)
{
}


void Bat::Init(MContent* content)
{
	this->img = content->LoadTexture("./bat.png");
	this->position = D3DXVECTOR2(0,105);	
	speed = 3;
}
void Bat::Update(float gameTime,MKeyboard* key)
{

	if(key->IsKeyDown(DIK_UP))
	{
		if(position.y > 0.0f)
			this->position.y -=speed;
	}
	if(key->IsKeyDown(DIK_DOWN))
	{
		if(position.y + 90.0f  < 300.0f )
			this->position.y +=speed;
	}
	rect.left = position.x;
	rect.right = rect.left + 30;
	rect.top = position.y;
	rect.bottom =  90;
}
void Bat::Render(MGraphic* graphic)
{
	graphic->DrawTexture(img,position,D3DCOLOR_XRGB(255,255,255));
}