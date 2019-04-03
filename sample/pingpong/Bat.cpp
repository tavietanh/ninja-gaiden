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
	this->position = D3DXVECTOR2(200,600 - 30);	
	speed = 3;
}
void Bat::Update(float gameTime,MKeyboard* key)
{

	if(key->IsKeyDown(DIK_LEFT))
	{
		if(position.x > 0.0f)
			this->position.x -=speed;
	}
	if(key->IsKeyDown(DIK_RIGHT))
	{
		if(position.x + 90.0f  < 300.0f )
			this->position.x +=speed;
	}
	rect.left = position.x;
	rect.right = rect.left + 90;
	rect.top = position.y;
	rect.bottom =  30;
}
void Bat::Render(MGraphic* graphic)
{
	graphic->DrawTexture(img,position,D3DCOLOR_XRGB(255,255,255));
}